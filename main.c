#include "print.h"
#include "scene.h"
#include "trace.h"

int main(void)
{
    int         i;
    int         j;
    double      u;
    double      v;

    t_color3    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
	t_object    *world;

    canv = canvas(400, 300);
    cam = camera(&canv, point3(0, 0, 0));
	world = object(SP, sphere(point3(-2, 0, -5), 2)); // world 에 구1 추가
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 990))); // world 에 구3 추가

    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);
            v = (double)j / (canv.height - 1);
            ray = ray_primary(&cam, u, v);
            pixel_color = ray_color(&ray, world);
            write_color(pixel_color);
            ++i;
        }
        --j;
    }
}