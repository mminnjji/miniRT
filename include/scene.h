/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:19:34 by man               #+#    #+#             */
/*   Updated: 2024/02/23 14:12:46 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_scene		*scene_init(t_arg *arg);
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 lookfrom, t_vec3 vd, double vfov);
t_object	*object(int type, void *element, t_color3 albedo);
t_sphere	*sphere(t_point3 center, double radius);
t_plane		*plane(t_point3 center, t_vec3 normal);
t_cylinder	*cylinder(t_point3 center, t_vec3 normal, \
double diameter, double height);
t_light		*light_point(t_point3 light_origin, \
t_color3 light_color, double b_r);
void		print_mlx(t_scene *s, double u, double v);

#endif