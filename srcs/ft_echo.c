/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/09 23:06:07 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo_n(int i, int tmp, t_env *env)
{
	char *new;

	if (env->flags[1])
	{
		i = 0;
		while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] != '-')
			i++;
		i += 2;
		while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33)
			i++;
		tmp = i;
		while (env->av_pipe[env->x][tmp])
			tmp++;
		while (env->av_pipe[env->x][tmp - 1]
		&& env->av_pipe[env->x][tmp - 1] < 33)
			tmp--;
		new = ft_substr(env->av_pipe[env->x], i, tmp - i);
		write(1, new, ft_strlen(new));
	}
}

void		ft_echo_two(t_env *env)
{
	int		i;
	int		tmp;
	char	*new;

	i = 0;
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33)
		i++;
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] > 32)
		i++;
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33)
		i++;
	tmp = i;
	while (env->av_pipe[env->x][tmp])
		tmp++;
	while (env->av_pipe[env->x][tmp - 1]
	&& env->av_pipe[env->x][tmp - 1] < 33)
		tmp--;
	new = ft_substr(env->av_pipe[env->x], i, tmp - i);
	write(1, new, ft_strlen(new));
}

void		ft_echo(t_env *env)
{
	if (env->flags[1] && !ft_strncmp(env->flags[1], "-n", 3))
	{
		ft_echo_n(0, 0, env);
		return ;
	}
	if (env->flags[1])
		ft_echo_two(env);
	write(1, "\n", 1);
}
