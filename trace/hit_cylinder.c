/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:10:33 by man               #+#    #+#             */
/*   Updated: 2024/02/23 17:26:42 by man              ###   ########.fr       */
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

int      hit_cylinder(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_vec3 oc;
	t_cylinder *cy;
	double	min;
	double	a;
	double	b;
	double	c;
	double	len;
	double	root;
	double	discri;
	t_vec3	av;
	t_vec3	bv;

	cy = world->element;
	oc = vminus(cy->center, ray->orig);
	av = vminus(vmult(cy->normal, vdot(cy->normal, ray->dir)), ray->dir);
	bv = vminus(oc, vmult(cy->normal, vdot(cy->normal, oc)));
	a = vdot(av, av);
	b = 2 * vdot(av, bv);
	c = vdot(bv, bv) - cy->diameter * cy->diameter;

	discri = b * b - 4 * a * c;
	if (discri < 0)
	{
		if (hit_cylinder_ud(world, ray, rec))
			return (1);
		return (0);
	}
	root = (-b - sqrt(discri)) / (2 * a);
	len = vdot(cy->normal, vminus(vmult(ray->dir, root), oc));
	if (root < rec->tmin || rec->tmax < root || len > cy->height / 2 || len < cy->height / 2 * -1)
	{
		min = hit_cylinder_ud(world, ray, rec);
		root = (-b + sqrt(discri)) / (2 * a);
		if (min && root > min)
			return (1);
		len = vdot(cy->normal, vminus(vmult(ray->dir, root), oc));
		if (root < rec->tmin || rec->tmax < root || len > cy->height / 2 || len < cy->height / 2 * -1) // 새로운 근도 범위에 없다면 리턴
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, vplus(cy->center, vmult(cy->normal, len))));
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (1);
}
