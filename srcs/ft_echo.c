/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/03/03 07:16:56 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			withoutspace(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (str[i - 1] && str[i - 1] < 33 && !nbslash(str, i - 1))
		i--;
	return (i);
}

void		ft_echo_n(int i, int tmp, t_env *env)
{
	char	*new;

	i = 0;
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] != '-')
		i++;
	i = next_none_space(env->av_pipe[env->x], i);
	i = next_space(env->av_pipe[env->x], i);
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33
	&& env->pipe[1][env->x][i] == '1')
		i++;
	tmp = i;
	while (env->av_pipe[env->x][tmp])
		tmp++;
	new = ft_substr(env->av_pipe[env->x], i, tmp - i);
	write(1, new, ft_strlen(new));
	free(new);
	new = NULL;
}

void		ft_echo_two(t_env *env)
{
	int		i;
	int		max;

	i = next_none_space(env->av_pipe[env->x], 0);
	i = next_space(env->av_pipe[env->x], i);
	while (env->av_pipe[env->x][i] && env->av_pipe[env->x][i] < 33
	&& env->pipe[1][env->x][i] == '1')
		i++;
	max = withoutspace(env->av_pipe[env->x] + i);
	while (env->av_pipe[env->x][i] && max--)
	{
		if (env->pipe[1][env->x][i] != '0')
			write(1, &env->av_pipe[env->x][i], 1);
		i++;
	}
}

void		ft_echo(t_env *env)
{
	if (env->flags[env->x][1] && !ft_strncmp(env->flags[env->x][1], "-n", 3))
	{
		ft_echo_n(0, 0, env);
		return ;
	}
	ft_echo_two(env);
	write(1, "\n", 1);
	free(env->pipe[1][env->x]);
	env->pipe[1][env->x] = NULL;
}
