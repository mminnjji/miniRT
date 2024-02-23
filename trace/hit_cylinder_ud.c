/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_ud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:46:07 by man               #+#    #+#             */
/*   Updated: 2024/02/23 17:46:08 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/trace.h"

int	hit_cylinder_ud_util(t_cylinder *cy, double root[], t_ray *ray)
{
	t_vec3		oc;

	oc = vminus(cy->center, ray->orig);
	root[2] = vdot(ray->dir, cy->normal);
	if (!root[2])
		return (0);
	root[0] = (vdot(oc, cy->normal) - cy->height * 0.5) / root[2];
	root[1] = (vdot(oc, cy->normal) + cy->height * 0.5) / root[2];
	return (1);
}

int	hit_cylinder_ud_(t_cylinder *cy, double r[], t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		b;
	t_vec3		uv;
	t_vec3		dv;

	a = r[r[3] == 1];
	b = r[r[3] == 0];
	uv = vplus(cy->center, \
	vmult(cy->normal, cy->height * 0.5 * ((r[3] == 1) * 2 - 1)));
	dv = vplus(cy->center, \
	vmult(cy->normal, cy->height * -0.5 * ((r[3] == 1) * 2 - 1)));
	if (a < rec->tmin || rec->tmax < a || \
	vlength3(uv, ray_at(ray, a)) > cy->diameter * cy->diameter)
	{
		if (b < rec->tmin || rec->tmax < b || \
		vlength3(dv, ray_at(ray, b)) > cy->diameter * cy->diameter)
			return (0);
		else
		{
			rec->normal = vmult(vunit(rec->normal), -1);
			rec->t = b;
		}
	}
	return (1);
}

int	hit_cylinder_ud(t_object *world, t_ray *ray, t_hit_record *rec)
{
	double		root[4];
	t_vec3		uv;
	t_vec3		dv;
	t_cylinder	*cy;

	cy = world->element;
	uv = vplus(cy->center, vmult(cy->normal, cy->height * 0.5));
	dv = vplus(cy->center, vmult(cy->normal, cy->height * -0.5));
	if (!hit_cylinder_ud_util(cy, root, ray))
		return (0);
	rec->normal = vmult(vunit(cy->normal), (root[1] <= root[0]));
	rec->t = root[(root[1] <= root[0])];
	root[3] = root[1] <= root[0];
	if (root[1] <= root[0])
	{
		if (!hit_cylinder_ud_(cy, root, ray, rec))
			return (0);
	}
	else
		if (!hit_cylinder_ud_(cy, root, ray, rec))
			return (0);
	rec->p = ray_at(ray, rec->t);
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (rec->t);
}
