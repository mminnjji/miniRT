/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_ud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:46:07 by man               #+#    #+#             */
/*   Updated: 2024/02/28 21:10:34 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/trace.h"

int	hit_cylinder_d(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_point3	dc;
	t_vec3		odc;
	double		droot;

	cy = world->element;
	dc = vplus(cy->center, vmult(cy->normal, cy->height * -0.5));
	odc = vminus(dc, ray->orig);
	droot = vdot(vmult(cy->normal, -1), ray->dir);
	if (droot != 0)
		droot = vdot(odc, vmult(cy->normal, -1)) / droot;
	else
		return (0);
	if (droot >= rec->tmin && rec->tmax >= droot && \
	vlength3(dc, ray_at(ray, droot)) <= cy->radius * cy->radius)
	{
		rec->t = droot;
		rec->p = ray_at(ray, droot);
		rec->normal = vunit(vmult(cy->normal, -1));
		set_face_normal(ray, rec);
		rec->albedo = world->albedo;
	}
	else
		return (0);
	return (1);
}

int	hit_cylinder_u(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_point3	uc;
	t_vec3		ouc;
	double		uroot;

	cy = world->element;
	uc = vplus(cy->center, vmult(cy->normal, cy->height * 0.5));
	ouc = vminus(uc, ray->orig);
	uroot = vdot(cy->normal, ray->dir);
	if (uroot != 0)
		uroot = vdot(ouc, cy->normal) / uroot;
	else
		return (0);
	if (uroot >= rec->tmin && rec->tmax >= uroot && \
	vlength3(uc, ray_at(ray, uroot)) <= cy->radius * cy->radius)
	{
		rec->t = uroot;
		rec->p = ray_at(ray, uroot);
		rec->normal = vunit(cy->normal);
		set_face_normal(ray, rec);
		rec->albedo = world->albedo;
	}
	else
		return (0);
	return (1);
}

int	hit_cylinder_ud(t_object *world, t_ray *ray, t_hit_record *rec)
{
	int	a;
	int	b;

	a = hit_cylinder_u(world, ray, rec);
	if (a)
		rec->tmax = rec->t;
	b = hit_cylinder_d(world, ray, rec);
	if (a || b)
		return (1);
	return (0);
}
