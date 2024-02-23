/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:34:34 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:18:52 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structures.h"
#include "../include/scene.h"

t_object	*object(int type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*plane(t_point3 center, t_vec3 normal)
{
	t_plane	*p;

	p = (t_plane *)malloc(sizeof(t_plane));
	if (!p)
		return (NULL);
	p->center = center;
	p->normal = vunit(normal);
	return (p);
}

t_cylinder	*cylinder(t_point3 center, t_vec3 normal, \
double diameter, double height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center = center;
	cy->normal = vunit(normal);
	cy->diameter = diameter;
	cy->height = height;
	return (cy);
}

t_light	*light_point(t_point3 light_origin, \
t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->orig = light_origin;
	light->l_c = light_color;
	light->b_r = bright_ratio;
	return (light);
}
