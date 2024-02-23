/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:24:49 by man               #+#    #+#             */
/*   Updated: 2024/02/23 14:13:39 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point3	point3(double x, double y, double z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point3	color3(double r, double g, double b)
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

// 벡터 변경 (좌표값)
void	vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vlength3(t_vec3 vec1, t_vec3 vec2)
{
	double	x;
	double	y;
	double	z;

	x = (vec1.x - vec2.x) * (vec1.x - vec2.x);
	y = (vec1.y - vec2.y) * (vec1.y - vec2.y);
	z = (vec1.z - vec2.z) * (vec1.z - vec2.z);
	return (x + y + z);
}
