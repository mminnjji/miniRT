/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:39 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:44:58 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	get_n(int fd)
{
	int		n;
	char	*tmp;

	n = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		++n;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (n);
}

char	**get_rt(int fd, char *str)
{
	char	**rt;
	char	*tmp;
	int		n;

	n = get_n(fd);
	fd = open(str, O_RDONLY);
	rt = malloc(sizeof(char *) * (n + 1));
	if (!rt)
		return (NULL);
	n = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		rt[n] = ft_strcpy(tmp);
		if (!rt[n])
			return (NULL);
		free(tmp);
		tmp = get_next_line(fd);
		n++;
	}
	rt[n] = 0;
	return (rt);
}

int	check_str_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
		str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	parse_util(char **r, t_arg **arg, int i)
{
	int	j;

	j = 0;
	if (!ft_smp(r[i], "A ", 2) || \
	!ft_smp(r[i], "C ", 2) || !ft_smp(r[i], "L ", 2))
		j = check_acl(r[i], arg);
	else if (!ft_smp(r[i], "sp ", 3) \
		|| !ft_smp(r[i], "pl ", 3) || !ft_smp(r[i], "cy ", 3))
		j = check_object(r[i], arg);
	else if (!check_str_blank(r[i]))
		return (1);
	return (j);
}

int	parse(int argc, char **argv, t_arg **arg)
{
	int		i[3];
	char	**r;

	if (argc != 2)
		return (1);
	i[0] = open(argv[1], O_RDONLY);
	if (i[0] < 0)
		return (1);
	r = get_rt(i[0], argv[1]);
	if (!r)
		return (1);
	i[1] = -1;
	i[2] = 0;
	while (r[++i[1]])
	{
		i[2] = parse_util(r, arg, i[1]);
		if (i[2])
			return (1);
	}
	ft_free2(r);
	return (0);
}
