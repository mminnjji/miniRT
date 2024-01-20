#ifndef TRACE_H
# define TRACE_H


# include "structures.h"
# include "util.h"
// 시작점 orig,  방향 dir
struct  s_ray 
{
    t_point3    orig;
    t_vec3      dir;
};

typedef struct s_ray t_ray;

# include "scene.h"

t_ray       ray(t_point3 orig, t_vec3 dir);
t_point3    ray_at(t_ray *ray, double t);
t_ray       ray_primary(t_camera *cam, double u, double v);

#endif