/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:39:14 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:28:16 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	ft_lstadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*tmp;

	tmp = (*lst);
	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	if (lst == NULL || new == NULL)
		return ;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = tmp;
}

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->type = NULL;
	arg->done = 0;
	arg->dtwo = 0;
	arg->p = point3(0, 0, 0);
	arg->v = vec3(0, 0, 0);
	arg->c = color3(0, 0, 0);
	arg->next = NULL;
	return (arg);
}

int	check_a(char *str, t_arg **arg)
{
	t_arg	*new;
	char	**tmp;

	new = init_arg();
	tmp = ft_split(str, ' ');
	if (!tmp || !new)
		return (1);
	if (ft_strlen2(tmp) != 3)
		return (ft_free2(tmp) + 1);
	if (check_d(tmp[1]))
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[2], 2))
		return (ft_free2(tmp) + 1);
	new->type = ft_strcpy(tmp[0]);
	if (!new->type)
		return (1);
	new->done = to_d(tmp[1]);
	new->c = to_point(tmp[2]);
	ft_free2(tmp);
	ft_lstadd_back(arg, new);
	return (0);
}

int	check_c(char *str, t_arg **arg)
{
	char	**tmp;
	t_arg	*new;

	new = init_arg();
	tmp = ft_split(str, ' ');
	if (!tmp || !new)
		return (1);
	if (ft_strlen2(tmp) != 4)
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[1], 0))
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[2], 1))
		return (ft_free2(tmp) + 1);
	if (check_d(tmp[3]))
		return (ft_free2(tmp) + 1);
	new->type = ft_strcpy(tmp[0]);
	if (!new->type)
		return (1);
	new->p = to_point(tmp[1]);
	new->v = to_point(tmp[2]);
	new->done = to_d(tmp[3]);
	ft_free2(tmp);
	ft_lstadd_back(arg, new);
	return (0);
}

int	check_l(char *str, t_arg **arg)
{
	char	**tmp;
	t_arg	*new;

	new = init_arg();
	tmp = ft_split(str, ' ');
	if (!tmp || !new)
		return (1);
	if (ft_strlen2(tmp) != 4)
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[1], 0))
		return (ft_free2(tmp) + 1);
	if (check_d(tmp[2]))
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[3], 2))
		return (ft_free2(tmp) + 1);
	new->type = ft_strcpy(tmp[0]);
	if (!new->type)
		return (1);
	new->p = to_point(tmp[1]);
	new->done = to_d(tmp[2]);
	new->c = to_point(tmp[3]);
	ft_free2(tmp);
	ft_lstadd_back(arg, new);
	return (0);
}
