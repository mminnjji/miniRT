/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:53:47 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:06:31 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int	get_ac(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

int	ft_free2(char **str)
{
	size_t	j;

	j = 0;
	while (str[j])
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (0);
}

static char	*get_len(char const *str, char c, int *k, int *tmp)
{
	char	*res;

	while (str[*k] == c)
		(*k)++;
	*tmp = *k;
	while (str[*k] != c && str[*k])
		(*k)++;
	res = (char *)malloc(sizeof(char) * (*k - *tmp + 1));
	if (!res)
		return (NULL);
	return (res);
}

static char	*get_str(char const *str, int k, int tmp, char *res)
{
	int	j;

	j = 0;
	while (j < k - tmp)
	{
		res[j] = str[j + tmp];
		j++;
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	res = (char **)malloc((get_ac(str, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < get_ac(str, c) && str[k])
	{
		res[i] = get_len(str, c, &k, &tmp);
		if (!res[i])
		{
			ft_free2(res);
			return (NULL);
		}
		res[i] = get_str(str, k, tmp, res[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
