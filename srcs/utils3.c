/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:55:11 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 09:30:34 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	how_many_redir(t_env *env)
{
	int	i;

	i = 0;
	while (env->copy_free[i])
	{
		if ((env->copy_free[i] == '>' || env->copy_free[i] == '<')
		&& !nbslash(env->copy_free, i))
			env->count_redir++;
		i++;
		if (env->copy_free[i] == '>' || env->copy_free[i] == '<')
			i++;
	}
}

int		free_syntax_error(t_env *env)
{
	ft_clear(&env->copy_free);
	return (1);
}

int		blank_line(t_env *env)
{
	int i;

	i = 0;
	while (env->copy_free[i])
	{
		if (env->copy_free[i] > 32)
			break ;
		i++;
	}
	if (env->copy_free[i])
		return (0);
	else
	{
		ft_clear(&env->copy_free);
		return (1);
	}
}

void	free_args(t_env *env)
{
	env->i = 0;
	while (env->args[env->i])
	{
		free(env->args[env->i]);
		env->args[env->i] = NULL;
		env->i++;
	}
	free(env->args);
	env->args = NULL;
}

void	free_pipe_two(t_env *env)
{
	free(env->pipe[1]);
	free(env->redir);
	free(env->isred);
	free(env->av_pipe);
	env->pipe[1] = NULL;
	env->redir = NULL;
	env->isred = NULL;
	env->av_pipe = NULL;
}

void	free_flags(t_env *env)
{
	int tab;
	int i;

	tab = 0;
	// dprintf(2, "6\n");
	i = 0;
	// dprintf(2, "6.2\n");
	while (env->flags[tab])
	{
		i = 0;
		// dprintf(2, "6tab{%p}\n", env->flags[tab]);
		// dprintf(2, "6.3\n");
		// dprintf(2, "6tab[i]{%p}\n", env->flags[tab][i]);
		while (env->flags[tab][i])
		{
			// dprintf(2, "6.4\n");
			free(env->flags[tab][i]);
			env->flags[tab][i] = NULL;
			i++;
			// dprintf(2, "6.5\n");
		}
		// dprintf(2, "6.6\n");
		free(env->flags[tab]);
		env->flags[tab] = NULL;
		tab++;
		// dprintf(2, "6.7\n");
	}
	// dprintf(2, "7\n");
	free(env->flags);
	// dprintf(2, "8\n");
	env->flags = NULL;
	// dprintf(2, "9\n");
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
	// dprintf(2, "5\n");
	free_flags(env);
	// dprintf(2, "12\n");
	free_pipe_two(env);
	// dprintf(2, "13\n");
}