/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lightening.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:38:41 by man               #+#    #+#             */
/*   Updated: 2024/02/23 14:14:02 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/trace.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, \
			point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

t_color3	point_light_get(t_scene *scene, t_light *l)
{
	t_color3	diffuse;
	t_vec3		l_dir;
	t_color3	spc;
	t_ray		l_ray;
	t_vec3		v_dir[2];

	l_dir = vminus(l->orig, scene->rec.p);
	l_ray = ray(vplus(scene->rec.p, \
	vmult(scene->rec.normal, EPSILON)), l_dir);
	if (in_shadow(scene->world, l_ray, vlength(l_dir)))
		return (color3(0, 0, 0));
	l_dir = vunit(l_dir);
	diffuse = vmult(l->l_c, fmax(vdot(scene->rec.normal, l_dir), 0.0));
	v_dir[0] = vunit(vmult(scene->ray.dir, -1));
	v_dir[1] = reflect(vmult(l_dir, -1), scene->rec.normal);
	spc = vmult(vmult(l->l_c, 0.5), pow(fmax(vdot(v_dir[0], v_dir[1]), 0), 64));
	return (vmult(vplus(vplus(scene->ambient, diffuse), spc), l->b_r * LUMEN));
}

int	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (1);
	return (0);
}
