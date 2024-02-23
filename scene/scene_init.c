/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:23:08 by man               #+#    #+#             */
/*   Updated: 2024/02/23 14:15:55 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/print.h"
#include "../include/scene.h"
#include "../include/trace.h"
#include "../include/parse.h"
#include "../mlx/mlx.h"

int	scene_init_util_1(t_scene **scene, t_arg *arg)
{
	arg->c = vdivide(arg->c, 255);
	if (!ft_smp(arg->type, "A", 1))
	{
		(*scene)->ambient = vmult(arg->c, arg->done);
		return (0);
	}
	if (!ft_smp(arg->type, "C", 1))
	{
		(*scene)->camera = \
		camera(&((*scene)->canvas), arg->p, arg->v, arg->done);
		return (1);
	}
	if (!ft_smp(arg->type, "L", 1))
	{
		(*scene)->light = object(LIGHT_POINT, \
		light_point(arg->p, color3(1, 1, 1), arg->done), color3(0, 0, 0));
		return (2);
	}
	return (-1);
}

void	scene_init_util_2(t_object **world, t_arg *arg)
{
	if (!ft_smp(arg->type, "sp", 2))
		oadd(world, object(SP, sphere(arg->p, arg->done), arg->c));
	if (!ft_smp(arg->type, "cy", 2))
		oadd(world, object(C, \
		cylinder(arg->p, arg->v, arg->done, arg->dtwo), arg->c));
	if (!ft_smp(arg->type, "pl", 2))
		oadd(world, object(P, plane(arg->p, arg->v), arg->c));
}

t_scene	*scene_init(t_arg *arg)
{
	int			c[4];
	t_scene		*scene;
	t_object	*world;

	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	world = NULL;
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->canvas = canvas(400, 300);
	while (arg)
	{
		c[3] = scene_init_util_1(&scene, arg);
		if (c[3] >= 0)
			c[c[3]]++;
		scene_init_util_2(&world, arg);
		arg = arg->next;
	}
	if (c[0] != 1 || c[1] != 1 || c[2] != 1)
		return (NULL);
	scene->world = world;
	return (scene);
}

int	print_mlx_util(int i[], double *u, double *v, t_scene **s)
{
	t_color3	pixel_color;
	int			j;

	pixel_color = color3(0, 0, 0);
	j = -1;
	while (++j < 100)
	{
		*u = (double)(i[1] + random_double()) / ((*s)->canvas.width - 1);
		*v = (double)(i[0] + random_double()) / ((*s)->canvas.height - 1);
		(*s)->ray = ray_primary(&((*s)->camera), *u, *v);
		pixel_color = vplus(ray_color(*s), pixel_color);
	}
	return (write_color(pixel_color));
}

// mlx로 출력
void	print_mlx(t_scene *s, double u, double v)
{
	int			i[3];
	void		*mlx;
	void		*mlx_win;
	t_data		img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, s->canvas.width, s->canvas.height, "miniRT");
	img.img = mlx_new_image(mlx, s->canvas.width, s->canvas.height);
	img.addr = mlx_get_data_addr(img.img, &img.bit_pixel, \
	&img.line_len, &img.endian);
	i[0] = s->canvas.height;
	while (--i[0] >= 0)
	{
		i[1] = -1;
		while (++i[1] < s->canvas.width)
		{
			i[2] = print_mlx_util(i, &u, &v, &s);
			my_mlx_pixel_put(&img, i[1], s->canvas.height - i[0] - 1, i[2]);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 3, 0, &key_press, NULL);
	mlx_hook(mlx_win, 17, 0, &closed, NULL);
	mlx_loop(mlx);
}
