#include "trace.h"

//ray init -> 점좌표 및 방향벡터(단위벡터 설정)
t_ray       ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir); // 방향벡터를 단위벡터로 설정해줌
    return (ray);
}

// orig 점에서 방향벡터로 t 만큼 간 경우의 좌표 반환
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t)); // ray에서 방향벡터로 t 만큼
    return (at);
}

//primary_ray 생성자 - 걍 시작 광선 만든다고 생각하셈 
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig;
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	// origin ~ right top 의 방향벡터가 될 것
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

t_color3    ray_color(t_ray *ray, t_object *world)
{
    double			t;
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
    if (hit(world, ray, &rec))
        return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
    else
    {
        t = 0.5 * (ray->dir.y + 1.0);
        return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0),     t)));
    }
}