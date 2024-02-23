/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:30:59 by man               #+#    #+#             */
/*   Updated: 2024/02/23 17:46:45 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

t_ray		ray(t_point3 orig, t_vec3 dir);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_point3	ray_at(t_ray *ray, double t);
t_color3	ray_color(t_scene *scene);
int			hit(t_object *obj, t_ray *ray, t_hit_record *rec);
int			hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
int			hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
int			hit_plane(t_object *world, t_ray *ray, t_hit_record *rec);
int			hit_cylinder(t_object *world, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);
t_color3	phong_lighting(t_scene *scene);
t_color3	point_light_get(t_scene *scene, t_light *light);
int			in_shadow(t_object *objs, t_ray light_ray, double light_len);
int			hit_cylinder_ud(t_object *world, t_ray *ray, t_hit_record *rec);

#endif