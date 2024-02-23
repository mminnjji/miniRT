/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:17:50 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:19:09 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/print.h"
#include <math.h>

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	write_color(t_color3 pixel_color)
{
	double	cc[3];
	double	scale;
	int		c_v[4];

	scale = 0.01;
	cc[0] = sqrt(pixel_color.x * scale);
	cc[1] = sqrt(pixel_color.y * scale);
	cc[2] = sqrt(pixel_color.z * scale);
	c_v[0] = (int)(255.999 * clamp(cc[0], 0.0, 0.999));
	c_v[1] = (int)(255.999 * clamp(cc[1], 0.0, 0.999));
	c_v[2] = (int)(255.999 * clamp(cc[2], 0.0, 0.999));
	return (c_v[0] / 16 * pow(16, 5) + c_v[0] % 16 * pow(16, 4) \
	+ c_v[1] / 16 * pow(16, 3) + c_v[1] % 16 * pow(16, 2) \
	+ c_v[2] / 16 * pow(16, 1) + c_v[2] % 16 * pow(16, 0));
}
