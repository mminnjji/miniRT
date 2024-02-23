/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:44:45 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:19:32 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scene.h"
#include <math.h>

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera	camera(t_canvas *canvas, t_point3 lookfrom, t_vec3 vd, double vfov)
{
	double		theta;
	t_camera	cam;
	double		viewport_height;
	t_vec3		v[3];

	theta = tan((vfov / 2.0) * (M_PI / 180.0));
	viewport_height = 2.0 * theta;
	v[0] = vunit(vd);
	if (vlength(vcross(vec3(0, 1, 0), v[0])))
		v[1] = vunit(vcross(vec3(0, 1, 0), v[0]));
	else
		v[1] = vunit(vcross(vec3(0, 1, 1), v[0]));
	v[2] = vcross(v[0], v[1]);
	cam.orig = lookfrom;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = 1.0;
	cam.horizontal = vmult(v[1], cam.viewport_w);
	cam.vertical = vmult(v[2], cam.viewport_h);
	cam.left_bottom = vminus(vminus(vplus(lookfrom, vmult(vd, cam.focal_len)), \
	vmult(cam.horizontal, 0.5)), vmult(cam.vertical, 0.5));
	return (cam);
}
