/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:10:10 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:17:55 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	ft_smp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	check_acl(char *str, t_arg **arg)
{
	int	res;

	res = 0;
	if (!ft_smp(str, "A ", 2))
		res = check_a(str, arg);
	else if (!ft_smp(str, "C ", 2))
		res = check_c(str, arg);
	else if (!ft_smp(str, "L ", 2))
		res = check_l(str, arg);
	return (res);
}

int	check_object(char *str, t_arg **arg)
{
	int	res;

	res = 0;
	if (!ft_smp(str, "sp ", 3))
		res = check_sp(str, arg);
	else if (!ft_smp(str, "pl ", 3))
		res = check_pl(str, arg);
	else if (!ft_smp(str, "cy ", 3))
		res = check_cy(str, arg);
	return (res);
}
