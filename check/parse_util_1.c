/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:43:14 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:28:16 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	check_d(char *str)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = ft_split(str, '.');
	if (!tmp)
		return (1);
	i = 0;
	j = 0;
	if (!(ft_strlen2(tmp) == 2 || ft_strlen2(tmp) == 1))
		return (ft_free2(tmp) + 1);
	while (tmp[i])
	{
		j = 0;
		if (i == 0 && tmp[i][0] == '-')
			j++;
		while (tmp[i][j])
		{
			if (!(tmp[i][j] <= '9' && tmp[i][j] >= '0'))
				return (ft_free2(tmp) + 1);
			j++;
		}
		i++;
	}
	return (ft_free2(tmp));
}

int	iscolor(double n)
{
	if (n >= 0 && n <= 255)
		return (1);
	return (0);
}

int	check_point(char *str, int flag)
{
	char	**t;

	t = ft_split(str, ',');
	if (!t)
		return (1);
	if (ft_strlen2(t) == 3)
	{
		if (!check_d(t[0]) && !check_d(t[1]) && !check_d(t[2]))
		{
			if (flag == 1)
			{
				if (!(to_d(t[0]) == 0 && to_d(t[1]) == 0 && to_d(t[2]) == 0))
					return (ft_free2(t));
			}
			if (flag == 2)
			{
				if (iscolor(to_d(t[0])) && iscolor(to_d(t[1])) \
				&& iscolor(to_d(t[2])))
					return (ft_free2(t));
			}
			if (flag == 0)
				return (ft_free2(t));
		}
	}
	return (ft_free2(t) + 1);
}
