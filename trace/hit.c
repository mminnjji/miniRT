/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:02:43 by man               #+#    #+#             */
/*   Updated: 2024/02/28 21:00:36 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/trace.h"

int	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	int				count;
	int				hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = 0;
	count = 0;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		count++;
		world = world->next;
	}
	return (hit_anything);
}

int	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	int	hit_result;
	int	a;
	int	b;

	hit_result = 0;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	if (world->type == P)
		hit_result = hit_plane(world, ray, rec);
	if (world->type == C)
	{
		a = hit_cylinder(world, ray, rec);
		if (a)
			rec->tmax = rec->t;
		b = hit_cylinder_ud(world, ray, rec);
		if (a || b)
			hit_result = 1;
	}
	return (hit_result);
}
