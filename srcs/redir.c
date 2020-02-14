/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:24:51 by antoine           #+#    #+#             */
/*   Updated: 2020/02/14 13:38:39 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_redir(t_env *env)
{
	int		i;

	i = 1;
	if (!(ft_strcmp(env->flags[0], ">")) || !(ft_strcmp(env->flags[0], ">>")))
		write(2, "Multi-line not supported\n", 25);
	while (env->flags[i])
	{
		if (!(ft_strcmp(env->flags[i], ">")) && env->flags[i + 1])
			env->fd_red = open(env->flags[i + 1], O_RDWR, O_CREAT);
		if (!(ft_strcmp(env->flags[i], ">>")) && env->flags[i + 1])
			env->fd_red = open(env->flags[i + 1], O_RDWR, O_CREAT, O_APPEND);
		i++;
	}
}
