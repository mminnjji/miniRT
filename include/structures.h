/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:05:46 by man               #+#    #+#             */
/*   Updated: 2024/02/28 15:13:53 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_camera		t_camera;
typedef struct s_canvas		t_canvas;
typedef struct s_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_hit_record	t_hit_record;
typedef struct s_light		t_light;
typedef struct s_scene		t_scene;
typedef struct s_material	t_material;
typedef struct s_plane		t_plane;
typedef struct s_data		t_data;
typedef struct s_arg		t_arg;

# define SP 0
# define P 1
# define C 2
# define LIGHT_POINT 3
# define EPSILON 1e-6
# define LUMEN 3

struct	s_data
{
	void	*img;
	char	*addr;
	int		bit_pixel;
	int		line_len;
	int		endian;
};

struct	s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct	s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct	s_camera
{
	t_point3	orig;
	double		viewport_h;
	double		viewport_w;
	double		focal_len;
	t_point3	left_bottom;
	t_vec3		horizontal;
	t_vec3		vertical;
};

struct	s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	int			front_face;
	t_color3	albedo;
};

struct	s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
};

struct	s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct	s_plane
{
	t_point3	center;
	t_vec3		normal;
};

struct	s_cylinder
{
	t_point3	center;
	t_vec3		normal;
	double		radius;
	double		height;
};

struct s_object
{
	int			type;
	void		*element;
	void		*next;
	t_color3	albedo;
};

struct	s_light
{
	t_point3	orig;
	t_color3	l_c;
	double		b_r;
};

struct	s_arg
{
	char			*type;
	double			done;
	double			dtwo;
	t_point3		p;
	t_vec3			v;
	t_color3		c;
	struct s_arg	*next;
};

double	random_double(void);

#endif