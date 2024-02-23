/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:28:51 by man               #+#    #+#             */
/*   Updated: 2024/02/23 15:28:16 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <limits.h>
# include "structures.h"
# include "utils.h"
# include "../gnl/get_next_line.h"

int			ft_smp(const char *s1, const char *s2, int n);
int			check_acl(char *str, t_arg **arg);
int			check_object(char *str, t_arg **arg);
char		**ft_split(char const *str, char c);
double		to_d(char *str);
t_point3	to_point(char *str);
int			ft_strlen2(char **tmp);
int			check_d(char *str);
int			iscolor(double n);
int			check_point(char *str, int flag);
int			parse(int argc, char **argv, t_arg **arg);
int			check_a(char *str, t_arg **arg);
int			check_c(char *str, t_arg **arg);
int			check_l(char *str, t_arg **arg);
int			check_cy(char *str, t_arg **arg);
int			check_sp(char *str, t_arg **arg);
int			check_pl(char *str, t_arg **arg);
t_arg		*init_arg(void);
void		ft_lstadd_back(t_arg **lst, t_arg *new);
int			ft_free2(char **str);
char		*ft_strcpy(char *dst);

#endif
