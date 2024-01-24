#include "scene.h"
#include <math.h>
t_camera    camera(t_canvas *canvas, t_point3 lookfrom, t_point3 lookat, t_vec3 vup, double vfov)
{
	double		theta;
    t_camera    cam;
    double      focal_len;
    double      viewport_height;

	theta = tan((vfov / 2.0) * (M_PI / 180.0));
    viewport_height = 2.0 * theta;
    focal_len = 1.0;

	t_vec3 w = vunit(vminus(lookfrom, lookat));
	t_vec3 u = vunit(vcross(vup, w));
	t_vec3 v = vcross(w, u);
    cam.orig = lookfrom;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vmult(u, cam.viewport_h);
    cam.vertical = vmult(v, cam.viewport_w);
    // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
                                vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    return (cam);
}