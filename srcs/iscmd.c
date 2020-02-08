/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/08 22:10:16 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	if (!ft_strncmp(cmd, "exit\0", 5))
		env->exit = 1;
	else if (!ft_strncmp(cmd, "echo\0", 5))
		ft_echo(cmd, env);
	else if (!(ft_strncmp(cmd, "pwd\0", 4)))
		ft_pwd();
	else if (!(ft_strncmp(cmd, "cd\0", 3)))
		ft_cd(env);
    else if (!(ft_strncmp(cmd, "clear\0", 6)))
        ft_clear();
	else if (!(ft_strncmp(cmd, "export\0", 7)))
		ft_export(cmd + 7, env);
	else if (!(ft_strncmp(cmd, "unset ", 6)))
		ft_unset(cmd, env);
	else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
		ft_env(env);
	else if (is_executable(env, 0))
		;
	else
		ft_not_found(cmd);
}

void	ft_pipe_is_cmd(t_env *env, int old_fd)
{
	int		pid;

	if (pipe(env->fd) < 0)
		exit(EXIT_FAILURE);
    if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
        close(env->fd[0]);
        dup2(env->fd[1], STDOUT_FILENO);
		if (old_fd > -1)
        	dup2(old_fd, STDIN_FILENO);
		env->flags = split_wh_sp(env->av_pipe[env->x]);
		is_command(env->flags[0], env);
        exit(0);
    }
	else
	{
        close(env->fd[1]);
        close(old_fd);
		old_fd = env->fd[0];
        if (env->av_pipe[++(env->x) + 1])
		{
            ft_pipe_is_cmd(env, old_fd);
		}
		else
		{
			if ((pid = fork()) < 0)
				exit(EXIT_FAILURE);
			if (pid == 0)
			{
				if (old_fd > -1)
					dup2(old_fd, STDIN_FILENO);
				env->flags = split_wh_sp(env->av_pipe[env->x]);
				is_command(env->flags[0], env);
				exit (0);
			}
			waitpid(pid, 0, 0);
		}
	}
    close(env->fd[0]);
}

void	ft_is_exit_here(t_env *env)
{
	env->x = 0;
	while (env->av_pipe[env->x])
	{
		if (!(env->av_pipe[env->x + 1]))
		{
			env->flags = split_wh_sp(env->av_pipe[env->x]);
			if (!ft_strcmp(env->flags[0], "exit\0"))
				exit(0);
		}
		env->x++;	
	}
	env->x = 0;
}

int		is_builtin_no_pipe(char *cmd, t_env *env)
{
	if (!ft_strncmp(cmd, "exit\0", 5) || !ft_strncmp(cmd, "echo\0", 5)
	|| !(ft_strncmp(cmd, "pwd\0", 4)) || !ft_strncmp(cmd, "cd\0", 3)
	||!ft_strncmp(cmd, "clear\0", 6) || !ft_strncmp(cmd, "export\0", 7)
	|| !ft_strncmp(cmd, "unset ", 6) || !ft_strncmp(cmd, "env", 3)
	|| !(ft_strncmp(cmd, "env ", 4)))
	{
		is_command(cmd, env);
		return (0);
	}
	else
		return (1);
	
}

void	is_pipe_here(t_env *env)
{
	int		pid;

	env->av_pipe = ft_split(env->args[env->i], '|');
	ft_is_exit_here(env);
	if (env->av_pipe[env->x + 1])
		ft_pipe_is_cmd(env, -1);
	else
	{

		env->flags = split_wh_sp(env->av_pipe[env->x]);
		dprintf(2, "|%s|\n", env->flags[0]);
		if (is_builtin_no_pipe(env->flags[0], env))
		{
			if ((pid = fork()) < 0)
				exit(EXIT_FAILURE);
			if (pid == 0)
			{
				is_command(env->flags[0], env);
				exit (0);
			}
			waitpid(pid, 0, 0);
		}
	}
	env->x = 0;
	while (env->av_pipe[env->x])
	{
		free(env->av_pipe[env->x]);
		env->av_pipe[env->x] = NULL;
		env->x++;
	}
	free(env->av_pipe);
	env->av_pipe = NULL;
}
