/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/03/03 13:56:19 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	if (!(env->ret = 0) && !ft_strncmp(cmd, "exit\0", 5))
		env->exit = 1;
	else if (!ft_strncmp(cmd, "echo\0", 5))
		ft_echo(env);
	else if (!(ft_strncmp(cmd, "pwd\0", 4)))
		ft_pwd();
	else if (!(ft_strncmp(cmd, "cd\0", 3)))
		ft_cd(env);
	else if (!(ft_strncmp(cmd, "clear\0", 6)))
		ft_clear_screen(env);
	else if ((!(ft_strncmp(cmd, "export\0", 7))) && env->flags[env->x][1])
		ft_export(env);
	else if ((!(ft_strncmp(cmd, "export\0", 7))) && (!env->flags[env->x][1]))
		env_malloc(env);
	else if (!(ft_strcmp(cmd, "unset")))
		ft_unset(env);
	else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
		ft_env(env);
	else if (is_executable(env, 0))
		;
	else
	{
		ft_not_found(cmd, env);
		env->ret = 127;
	}
}

void	ft_pipe_is_cmd(t_env *env, int old_fd)
{
	int		pid;

	if (pipe(env->fd) < 0)
		exit(EXIT_FAILURE);
	if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_ps(env, old_fd);
	else
		parent_ps(env, old_fd, pid);
	close(env->fd[0]);
}

void	ft_is_exit_here(t_env *env)
{
	env->x = 0;
	while (env->av_pipe[env->x])
		env->x++;
	if (!(env->flags = (char***)malloc(sizeof(char**) * (env->x + 1))))
		return ;
	env->x = 0;
	while (env->av_pipe[env->x])
	{
		env->flags[env->x] = split_wh_sp(env->av_pipe[env->x]);
		if (!(env->av_pipe[env->x + 1]))
			if (!ft_strcmp(env->flags[env->x][0], "exit\0"))
			{
				if (env->flags[env->x][1])
					exit(ft_atoi(env->flags[env->x][1]));
				else
					exit(0);
			}
		env->x++;
	}
	env->flags[env->x] = 0;
}

int		is_builtin_no_pipe(char *cmd, t_env *env)
{
	(void)env;
	if (!ft_strncmp(cmd, "exit\0", 5) || !ft_strncmp(cmd, "echo", 5)
	|| !ft_strncmp(cmd, "pwd\0", 4) || !ft_strncmp(cmd, "cd\0", 3)
	|| !ft_strncmp(cmd, "clear\0", 6) || !ft_strncmp(cmd, "export\0", 7)
	|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
	|| !ft_strncmp(cmd, "env ", 4))
		return (0);
	else
		return (1);
}

void	is_pipe_here(t_env *env)
{
	if (!(env->redir = (char**)malloc(sizeof(char*) * (env->count_redir + 1))))
		return ;
	env->av_pipe = split_pipes(env);
	ft_is_exit_here(env);
	env->x = 0;
	if (env->av_pipe[env->x + 1])
		ft_pipe_is_cmd(env, -1);
	else
		is_pipe_here_two(env);
	free_pipe(env, 0, 0);
}
