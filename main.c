/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:14:48 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:20:10 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structures.h"
#include "include/utils.h"
#include "include/print.h"
#include "include/scene.h"
#include "include/trace.h"
#include "mlx/mlx.h"
#include "include/parse.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_pixel / 8));
	*(unsigned int *)dst = color;
}

// 계단 현상을 없애기 위해 좌표 근처 랜덤값을 불러옴 
double	random_double(void)
{
	double	res;

	res = rand() % 100;
	res = res / 100;
	return (res);
}

int	closed(int key_code)
{
	(void)key_code;
	exit(0);
	return (0);
}

int	key_press(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg		*arg;
	double		u;
	double		v;
	t_scene		*scene;

	u = 0;
	v = 0;
	arg = NULL;
	if (parse(argc, argv, &arg))
	{
		printf("error1\n");
		return (1);
	}
	scene = scene_init(arg);
	if (!scene)
	{
		printf("error2\n");
		return (1);
	}
	print_mlx(scene, u, v);
	ft_lstclear(&arg);
	ft_lstclear2(&(scene->world));
	free(scene->light);
	free(scene);
	return (0);
}
