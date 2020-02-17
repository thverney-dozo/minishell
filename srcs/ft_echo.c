/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/16 16:49:17 by thverney         ###   ########.fr       */
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
		while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33
		&& env->cpy_pipe[env->x][i] == '1')
			i++;
		tmp = i;
		while (env->av_pipe[env->x][tmp])
			tmp++;
		new = ft_substr(env->av_pipe[env->x], i, tmp - i);
		write(env->fd_red, new, ft_strlen(new));
	}
}

void		ft_echo_two(t_env *env)
{
	int		i;
	int		tmp;
	char	*new;

	i = next_none_space(env->av_pipe[env->x], 0);
	i = next_space(env->av_pipe[env->x], i);
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33
	&& env->cpy_pipe[env->x][i] == '1')
		i++;
	tmp = i;
	while (env->av_pipe[env->x][tmp])
		tmp++;
	new = ft_substr(env->av_pipe[env->x], i, tmp - i);
	write(env->fd_red, new, ft_strlen(new));
}

void		ft_echo(t_env *env)
{
	// dprintf(2, "Je suis rentré dans echo \n◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊◊\n");
	if (env->flags[1] && !ft_strncmp(env->flags[1], "-n", 3))
	{
		ft_echo_n(0, 0, env);
		return ;
	}
	ft_echo_two(env);
	write(env->fd_red, "\n", 1);
}
