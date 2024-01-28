#include <stdio.h>
#include "structures.h"
#include "utils.h"
#include "print.h"
#include "scene.h"
#include "trace.h"

double random_double()
{
	double res;

	res = rand() % 100;
	res = res / 100;
	return (res);
}

double random_double2()
{
	double res;

	res = rand() % 201;
	res = res / 200 - 1;
	return (res);
}

t_vec3 random_vector()
{
	t_vec3 new;
	while (1)
	{
		new = vec3(random_double2(), random_double2(), random_double2());
		if (!(new.x == 0 && new.y == 0 && new.z == 0))
			break;
	}
	return (new);
}

t_vec3 random_in_unit_sphere()
{
	t_vec3 p;
    while (1)
	{
        p = random_vector();
        if (vlength2(p) < 1)
            return (p);
    }
}

t_vec3 random_unit_vector()
{
    return vunit(random_in_unit_sphere());
}

t_vec3 random_on_hemisphere(t_vec3 normal)
{
    t_vec3 on_sphere = random_unit_vector();
    if (vdot(on_sphere, normal) > 0.0)
        return (on_sphere);
    else
        return (vmult(on_sphere, -1));
}

t_scene	*scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka; 

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0), point3(0, 0, -5), vec3(0,1,0), 90);
    world = object(SP, sphere(point3(0, -2000, -5), 1999), color3(1, 1, 1));
	//world = object(SP, sphere(point3(3, 0, -5), 3), color3(0.2, 0.5, 0.9));
	oadd(&world, object(C, cylinder(point3(1, 2, -5), vec3(0, 1, 0), 1.0, 2.0), color3(0.5, 0, 0.5)));
	//oadd(&world, object(SP, sphere(point3(3, 0, -5), 3), color3(0.2, 0.5, 0.9)));
    //oadd(&world, object(P, plane(point3(0, -, -5), vec3(0, 1, 0)), color3(1, 0, 0)));
	//oadd(&world, object(SP, sphere(point3(-3, 0, -5), 1), color3(0.9, 0.6, 0)));
	scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(-10, 10, -5), color3(1, 1, 1), 0.7), color3(0, 0, 0));
    scene->light = lights;
    ka = 0.1; 
    scene->ambient = vmult(color3(1,1,1), ka); 
    return (scene);
}

int	main(void)
{
    int     i;
    int     j;
	double      u;
    double      v;
    t_color3    pixel_color;
	t_scene     *scene;

	scene = scene_init();
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = scene->canvas.height - 1;
	while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
			pixel_color = color3(0, 0, 0);
			for (int s = 0; s < 100; ++s)
			{
				u = (double)(i + random_double()) / (scene->canvas.width - 1);
				v = (double)(j + random_double()) / (scene->canvas.height - 1);		
				scene->ray = ray_primary(&scene->camera, u, v);
				pixel_color = vplus(ray_color(scene), pixel_color);
			}
            write_color(pixel_color);
            ++i;
        }
        --j;
    }
    return (0);
}