/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:31:38 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:30:12 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	plus;
	long long	sum;

	i = 0;
	plus = 1;
	sum = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) \
				|| str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			plus *= -1;
	while (ft_isdigit(str[i]))
	{
		if ((sum == LLONG_MAX / 10 && str[i] > \
					LLONG_MAX % 10 + '0' + (plus != 1)) \
					|| sum > LLONG_MAX / 10)
			return (-1 * ((plus == 1)));
		sum *= 10;
		sum += (str[i++] - '0');
	}
	return ((sum * plus));
}

double	to_d(char *str)
{
	double	res;
	double	b;
	int		n;
	char	**tmp;

	b = 0;
	tmp = ft_split(str, '.');
	if (!tmp)
		return (1);
	if (tmp[1])
	{
		n = ft_strlen(tmp[1]);
		if (n != 0)
		{
			while (tmp[1][n - 1] == '0')
				n--;
		}
		tmp[1][n] = 0;
		n = pow(10, n);
		b = ft_atoi(tmp[1]) / (double)n;
	}
	res = ft_atoi(tmp[0]) - b * ((ft_atoi(tmp[0]) < 0) * 2 - 1);
	ft_free2(tmp);
	return (res);
}

t_point3	to_point(char *str)
{
	char		**tmp;
	t_point3	p;

	tmp = ft_split(str, ','); // 이거 말록오류 일때 어떻게 해제해야 하는지 모르겟음
	p = point3(to_d(tmp[0]), to_d(tmp[1]), to_d(tmp[2]));
	ft_free2(tmp);
	return (p);
}

int	ft_strlen2(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}
