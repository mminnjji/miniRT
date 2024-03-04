/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:02:43 by man               #+#    #+#             */
/*   Updated: 2024/02/28 12:35:02 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/trace.h"

// 구에 hit
int	hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	double		d[4];
	double		root;

	sp = world->element;
	d[0] = vlength2(ray->dir);
	d[1] = vdot(vminus(ray->orig, sp->center), ray->dir);
	d[2] = vlength2(vminus(ray->orig, sp->center)) - sp->radius2;
	if (d[1] * d[1] - d[0] * d[2] < 0)
		return (0);
	d[3] = sqrt(d[1] * d[1] - d[0] * d[2]);
	root = (-d[1] - d[3]) / d[0];
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-d[1] + d[3]) / d[0];
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, sp->center));
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (1);
}

int	hit_plane(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc;
	t_plane	*p;
	double	root;

	p = world->element;
	oc = vminus(p->center, ray->orig);
	p = world->element;
	root = vdot(p->normal, ray->dir);
	if (root != 0)
		root = vdot(oc, p->normal) / root;
	else
		return (0);
	if (root < rec->tmin || rec->tmax < root)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(p->normal);
	set_face_normal(ray, rec);
	rec->albedo = world->albedo;
	return (1);
}
