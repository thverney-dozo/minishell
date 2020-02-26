/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:55:11 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 14:04:51 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_flags(t_env *env)
{
	int tab;
	int i;

	tab = 0;
	i = 0;
	while (env->flags[tab])
	{
		i = 0;
		while (env->flags[tab][i])
		{
			free(env->flags[tab][i]);
			env->flags[tab][i] = NULL;
			i++;
		}
		free(env->flags[tab]);
		env->flags[tab] = NULL;
		tab++;
	}
	free(env->flags);
	env->flags = NULL;
}

void	free_pipe_fork(t_env *env, int i, int pipe)
{
	while (env->av_pipe[pipe])
	{
		free(env->av_pipe[pipe]);
		env->av_pipe[pipe++] = NULL;
	}
	while (env->pipe[1][i])
	{
		free(env->pipe[1][i]);
		env->pipe[1][i++] = NULL;
	}
	free_flags(env);
	free_pipe_two(env);
	free_args(env);
}

void	free_pipe(t_env *env, int i, int pipe)
{
	while (env->av_pipe[pipe])
	{
		free(env->av_pipe[pipe]);
		env->av_pipe[pipe++] = NULL;
	}
	while (env->pipe[1][i])
	{
		free(env->pipe[1][i]);
		env->pipe[1][i++] = NULL;
	}
	free_flags(env);
	free_pipe_two(env);
}
