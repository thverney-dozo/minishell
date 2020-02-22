/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:21:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/22 19:36:38 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_ps(t_env *env, int old_fd)
{
	close(env->fd[0]);
	dup2(env->fd[1], STDOUT_FILENO);
	if (old_fd > -1)
		dup2(old_fd, STDIN_FILENO);
	env->flags = split_wh_sp(env->av_pipe[env->x]);
	env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
	is_command(env->flags[0], env);
	env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
	exit(0);
}

void	parent_ps(t_env *env, int old_fd, int pid)
{
	close(env->fd[1]);
	close(old_fd);
	old_fd = env->fd[0];
	if (env->av_pipe[++(env->x) + 1])
		ft_pipe_is_cmd(env, old_fd);
	else
	{
		if ((pid = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (old_fd > -1)
				dup2(old_fd, STDIN_FILENO);
			env->flags = split_wh_sp(env->av_pipe[env->x]);
			env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
			is_command(env->flags[0], env);
			env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
			exit(0);
		}
		waitpid(pid, 0, 0);
	}
}

void	is_pipe_here_two(t_env *env)
{
	int pid;

	env->flags = split_wh_sp(env->av_pipe[env->x]);
	if (is_builtin_no_pipe(env->flags[0], env))
	{
		if ((pid = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
			is_command(env->flags[0], env);
			env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
			exit(0);
		}
		waitpid(pid, 0, 0);
	}
	else
	{
		env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
		is_command(env->flags[0], env);
		env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
	}
}
