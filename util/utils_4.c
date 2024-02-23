/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:24:49 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:19:59 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

t_vec3	vcross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

t_vec3	vunit(t_vec3 vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

void	ft_lstclear(t_arg **lst)
{
	t_arg	*tmp;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->type);
		free(tmp);
	}
	free(*lst);
	(*lst) = NULL;
}

void	ft_lstclear2(t_object **lst)
{
	t_object	*tmp;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp);
	}
	free(*lst);
	(*lst) = NULL;
}
