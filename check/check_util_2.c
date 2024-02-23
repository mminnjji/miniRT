/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:20:06 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:28:16 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

char	*ft_strcpy(char *dst)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(dst) + 1));
	if (!res)
		return (NULL);
	while (dst[i])
	{
		res[i] = dst[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	check_sp(char *str, t_arg **arg)
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

int	check_pl(char *str, t_arg **arg)
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
	if (check_point(tmp[3], 2))
		return (ft_free2(tmp) + 1);
	new->type = ft_strcpy(tmp[0]);
	if (!new->type)
		return (1);
	new->p = to_point(tmp[1]);
	new->v = to_point(tmp[2]);
	new->c = to_point(tmp[3]);
	ft_free2(tmp);
	ft_lstadd_back(arg, new);
	return (0);
}

int	check_cy(char *str, t_arg **arg)
{
	char	**tmp;
	t_arg	*new;

	new = init_arg();
	tmp = ft_split(str, ' ');
	if (!tmp || !new)
		return (1);
	if (ft_strlen2(tmp) != 6)
		return (ft_free2(tmp) + 1);
	if (check_point(tmp[1], 0) || check_point(tmp[2], 1))
		return (ft_free2(tmp) + 1);
	if (check_d(tmp[3]) || check_d(tmp[4]) || check_point(tmp[5], 2))
		return (ft_free2(tmp) + 1);
	new->type = ft_strcpy(tmp[0]);
	if (!new->type)
		return (1);
	new->p = to_point(tmp[1]);
	new->v = to_point(tmp[2]);
	new->done = to_d(tmp[3]);
	new->dtwo = to_d(tmp[4]);
	new->c = to_point(tmp[5]);
	ft_free2(tmp);
	ft_lstadd_back(arg, new);
	return (0);
}
