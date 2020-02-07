/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/07 14:52:31 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strncmp(cmd, "exit ", 5)
	|| !ft_strncmp(cmd, "exit;", 5))
		exit(1);
	else if (!(ft_strncmp(cmd, "echo ", 5)) || !ft_strncmp(cmd, "echo", 5)
	|| !(ft_strncmp(cmd, "echo;", 5)))
		ft_echo(cmd);
	else if (!(ft_strncmp(cmd, "pwd", 4)) || !(ft_strncmp(cmd, "pwd ", 4))
	|| !(ft_strncmp(cmd, "pwd;", 4)))
		ft_pwd(cmd, 3);
	else if (!(ft_strncmp(cmd, "cd", 2)))
		ft_cd(cmd + 3, env);
    else if (!(ft_strcmp(cmd, "clear")))
        ft_clear();
	else if (!(ft_strncmp(cmd, "export ", 7)))
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

void	ft_pipe_is_cmd(t_env *env)
{
	pid_t pid;
	int status;

	if (env->av_pipe[env->x] && env->av_pipe[env->x + 1])
		if (pipe(env->fd) < 0)
			exit(EXIT_FAILURE);
	if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
////////////////////////////////////////////////////////////////////////////////////
	if (pid == 0)
	{
		// close(env->fd[0]);
		// if (env->is_fd >= 0)
		// {
			// printf("|%s||%d|\n",env->av_pipe[env->x] ,env->is_fd);
			// dup2(env->fd[1], 0);
		// }
		// dup2(1, env->fd[1]);
		is_command(env->av_pipe[env->x] + env->y, env);
	}
//////////////////////////////////////////////////////////////////////////////////////
	else if(env->av_pipe[env->x] && env->av_pipe[env->x + 1])
	{
		close(env->fd[1]);
		// dup2(0, env->fd[0]);
		waitpid(pid, &status, 0);
	}
	else 
	{
		close(env->fd[1]);
		dup2(0, env->fd[0]);
		waitpid(pid, &status, 0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////

void	is_pipe_here(t_env *env)
{
	env->is_fd = -1;
	if (ft_strchr(env->args[env->i], '|'))
	{
		env->av_pipe = ft_split(env->args[env->i], '|');
		env->x = 0;
		env->flags = split_wh_sp(env->av_pipe[env->x]);
		while (env->av_pipe[env->x] && env->av_pipe[env->x + 1])
		{
			env->y = 0;
			while (env->av_pipe[env->x][env->y] < 33 && env->av_pipe[env->x][env->y])
				env->y++;
			ft_pipe_is_cmd(env);
			env->is_fd = 1;
			free(env->av_pipe[env->x]);
			env->av_pipe[env->x] = NULL;
			env->x++;
		}
		env->av_pipe[env->x] ? ft_pipe_is_cmd(env) : 0;	
	}
	else
	{
		env->av_pipe = ft_split(env->args[env->i], '|');
		env->flags = split_wh_sp(env->args[env->i]);
		ft_pipe_is_cmd(env);
	}
	free(env->av_pipe);
	env->av_pipe = NULL;
}
