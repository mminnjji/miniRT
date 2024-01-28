#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool          hit_anything;
    t_hit_record    temp_rec;

    temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
    hit_anything = FALSE;
    while(world)
    {
        if (hit_obj(world, ray, &temp_rec))
        {
            hit_anything = TRUE;
            temp_rec.tmax = temp_rec.t;
            *rec = temp_rec;
        }
        world = world->next;
    }
    return (hit_anything);
}

// hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
t_bool      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool  hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec);
	if (world->type == P)
        hit_result = hit_plane(world, ray, rec);
	if (world->type == C)
    	hit_result = hit_cylinder(world, ray, rec);
    return (hit_result);
}

t_bool      hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_sphere    *sp;
    t_vec3  oc; //방향벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a;
    double  half_b;
    double  c;
    double  discriminant; //판별
	double  sqrtd;
    double  root;

	sp = world->element;
    oc = vminus(ray->orig, sp->center);
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    // discriminant 는 판별식 -> 근은 원점에서 구의 표면 까지의 거리 
    discriminant = half_b * half_b - a * c; // 걍 전체를 4로 나눈거임
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a; // 근의 공식 - 위를 2로 나눠서 처리해준 것 +- 공식이므로 작은 것 부터 확인
	if (root < rec->tmin || rec->tmax < root) // 근이 최솟값 보다 작거나 최댓값 보다 클 때
	{
		root = (-half_b + sqrtd) / a; // 새로운 근을 구함
		if (root < rec->tmin || rec->tmax < root) // 새로운 근도 범위에 없다면 리턴
			return (FALSE);
	}
	//충족하는 근이 존재할 때
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vdivide(vminus(rec->p, sp->center), sp->radius)); 
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (TRUE);
}


t_bool      hit_plane(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_plane	*p;

	double root;
	p = world->element;
	
	root = vdot(p->normal, ray->dir);
	if (root != 0)
		root = vdot(vminus(p->center, ray->orig), p->normal) / root;
	else
		return (FALSE);
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);

	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(p->normal);
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (TRUE);
}

t_bool		hit_cylinder_ud(t_object *world, t_ray *ray, t_hit_record *rec)
{
	double a;
	double b;
	double root;
	t_vec3 oc;
	t_vec3 un;
	t_vec3 dn;
	t_cylinder *cy;

	cy = world->element;
	oc = vminus(cy->center, ray->orig);
	un = vplus(oc, vmult(cy->normal, cy->height * 0.5)); // o-c8
	dn = vplus(oc, vmult(cy->normal, cy->height * 0.5 * -1)); //o-c7
	a = vdot(cy->normal, ray->dir);
	b = vdot(cy->normal, oc);
	if (a)
	{
		root = (b + cy->height * 0.5) / a;
		if (root > rec->tmin && rec->tmax > root && vlength3(un, ray_at(ray, root)) <= cy->diameter)
		{
			rec->t = root;
			rec->p = ray_at(ray, root);
			rec->normal = vunit(cy->normal);
			set_face_normal(ray, rec);
			rec->albedo = world->albedo;
			return (TRUE);
		}
		else
		{
			root = (b - cy->height * 0.5) / a;
			if (root > rec->tmin && rec->tmax > root && vlength3(dn, ray_at(ray, root)) <= cy->diameter)
			{
				rec->t = root;
				rec->p = ray_at(ray, root);
				rec->normal = vunit(vmult(cy->normal, -1));
				set_face_normal(ray, rec);
				rec->albedo = world->albedo;
				return (TRUE);
			}
			else
				return (FALSE);
		}
	}
	else
		return (FALSE);
}

t_bool      hit_cylinder(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_vec3 oc;
	t_cylinder *cy;
	double root;
	t_vec3 ap;
	double a;
	t_vec3 bp;
	double b;
	double c;
	double sqrtd;
	double discriminant;
	double len;

	cy = world->element;
	oc = vminus(cy->center, ray->orig);
	ap = vminus(ray->dir, vmult(cy->normal, vdot(cy->normal, ray->dir)));
	bp = vminus(vmult(cy->normal, vdot(cy->normal, oc)), oc);
	a = vdot(ap, ap);
	b = 2 * vdot(ap, bp);
	c = vdot(bp, bp) - cy->diameter * cy->diameter;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / (2 * a); // 근의 공식 - 위를 2로 나눠서 처리해준 것 +- 공식이므로 작은 것 부터 확인
	len = vdot(cy->normal, vminus(ray_at(ray,root), oc));
	if (root < rec->tmin || rec->tmax < root || len > cy->height / 2 || len < cy->height / 2 * -1) // 근이 최솟값 보다 작거나 최댓값 보다 클 때
	{
		if (hit_cylinder_ud(world, ray, rec))
			return (TRUE);
		root = (-b + sqrtd) / (2 * a); // 새로운 근을 구함
		len = vdot(cy->normal, vminus(ray_at(ray,root), vminus(cy->center, ray->orig)));
		if (root < rec->tmin || rec->tmax < root || len > cy->height / 2 || len < cy->height / 2 * -1) // 새로운 근도 범위에 없다면 리턴
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, vplus(cy->center, vmult(cy->normal, len))));
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (TRUE);
}