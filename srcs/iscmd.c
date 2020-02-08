/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/08 07:29:03 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	int i;

	i = 0;
	while (cmd[i] < 33 && cmd[i])
		i++;
	if (!ft_strcmp(cmd + i, "exit") || !ft_strncmp(cmd + i, "exit ", 5)
	|| !ft_strncmp(cmd + i, "exit;", 5))
		exit(1);
	else if (!(ft_strncmp(cmd + i, "echo ", 5)) || !ft_strncmp(cmd + i, "echo", 5)
	|| !(ft_strncmp(cmd + i, "echo;", 5)))
		ft_echo(cmd + i);
	else if (!(ft_strncmp(cmd + i, "pwd", 4)) || !(ft_strncmp(cmd + i, "pwd ", 4))
	|| !(ft_strncmp(cmd + i, "pwd;", 4)))
		ft_pwd(cmd + i, 3);
	else if (!(ft_strncmp(cmd + i, "cd", 2)))
		ft_cd(cmd + i + 3, env);
    else if (!(ft_strcmp(cmd + i, "clear")))
        ft_clear();
	else if (!(ft_strncmp(cmd + i, "export ", 7)))
		ft_export(cmd + i + 7, env);
	else if (!(ft_strncmp(cmd + i, "unset ", 6)))
		ft_unset(cmd + i, env);
	else if (!(ft_strncmp(cmd + i, "env", 3) || !(ft_strncmp(cmd + i, "env ", 4))))
		ft_env(env);
	else if (is_executable(env, 0))
		;
	else
		ft_not_found(cmd);
}

void	ft_pipe_is_cmd(t_env *env, int old_fd)
{
    // int     status;
    // pid_t   child_right;
    // pid_t   child_left;
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
		is_command(env->av_pipe[env->x], env);
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
				is_command(env->av_pipe[(env->x)], env);
				exit (0);
			}
			waitpid(pid, 0, 0);
		}
	}
    close(env->fd[0]);
}

void	is_pipe_here(t_env *env)
{
	env->av_pipe = ft_split(env->args[env->i], '|');
	env->x = 0;
	// env->flags = split_wh_sp(env->av_pipe[env->x]);
	if (env->av_pipe[env->x + 1])
		ft_pipe_is_cmd(env, -1);
	else
	{
		int		pid;
	
		if ((pid = fork()) < 0)
				exit(EXIT_FAILURE);
		if (pid == 0)
		{
			// if (old_fd > -1)
			// 	dup2(old_fd, STDIN_FILENO);
			is_command(env->av_pipe[(env->x)], env);
			exit (0);
		}
		waitpid(pid, 0, 0);
	}
	// is_command(env->av_pipe[env->x], env);
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
