/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:10:33 by man               #+#    #+#             */
/*   Updated: 2024/02/23 17:46:21 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/trace.h"

int	hit_cylinder_util(t_ray *ray, t_cylinder *cy, double d[], t_vec3 oc)
{
	t_vec3	av;
	t_vec3	bv;

	av = vminus(vmult(cy->normal, vdot(cy->normal, ray->dir)), ray->dir);
	bv = vminus(oc, vmult(cy->normal, vdot(cy->normal, oc)));
	d[0] = vdot(av, av);
	d[1] = 2 * vdot(av, bv);
	d[2] = vdot(bv, bv) - cy->diameter * cy->diameter;
	d[3] = d[1] * d[1] - 4 * d[0] * d[2];
	if (d[3] < 0)
		return (1);
	d[6] = (-d[1] - sqrt(d[3])) / (2 * d[0]);
	d[5] = vdot(cy->normal, vminus(vmult(ray->dir, d[6]), oc));
	return (0);
}

void	hit_cylinder_(t_object *world, t_ray *ray, \
t_hit_record *rec, double d[])
{
	t_cylinder	*cy;

	cy = world->element;
	rec->t = d[6];
	rec->p = ray_at(ray, d[6]);
	rec->normal = vunit(vminus(rec->p, \
	vplus(cy->center, vmult(cy->normal, d[5]))));
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
}

int	hit_cylinder(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_vec3		oc;
	t_cylinder	*cy;
	double		d[7];

	cy = world->element;
	oc = vminus(cy->center, ray->orig);
	if (hit_cylinder_util(ray, cy, d, oc))
		return (hit_cylinder_ud(world, ray, rec));
	if (d[6] < rec->tmin || rec->tmax < d[6] \
	|| d[5] > cy->height / 2 || d[5] < cy->height / 2 * -1)
	{
		d[4] = hit_cylinder_ud(world, ray, rec);
		d[6] = (-d[1] + sqrt(d[3])) / (2 * d[0]);
		if (d[4] && d[6] > d[4])
			return (1);
		d[5] = vdot(cy->normal, vminus(vmult(ray->dir, d[6]), oc));
		if (d[6] < rec->tmin || rec->tmax < d[6] \
		|| d[5] > cy->height / 2 || d[5] < cy->height / 2 * -1)
			return (0);
	}
	hit_cylinder_(world, ray, rec, d);
	return (1);
}
