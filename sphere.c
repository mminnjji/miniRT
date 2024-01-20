#include "scene.h"
#include "util.h"
#include "trace.h"

// 오브젝트 만들때 호출
t_object    *object(t_object_type type, void *element)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    return (new);
}

// 구 만들 때 호출
t_sphere    *sphere(t_point3 center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

void    set_face_normal(t_ray *r, t_hit_record *rec)
{
    // 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
    rec->front_face = vdot(r->dir, rec->normal) < 0;
    // 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
    rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}

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
        hit_result = hit_sphere(world, ray, rec); //hit_sphere의 첫번째 인자도 t_sphere *에서 t_object *로 수정해주자.
    return (hit_result);
}

t_bool      hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc; //방향벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a;
    double  half_b;
    double  c;
    double  discriminant; //판별
	double  sqrtd;
    double  root;
	t_sphere *sp;

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
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); 
	set_face_normal(ray, rec);
	return (TRUE);
}