/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/17 03:06:40 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	//dprintf(2, "je suis rentré dans iscmd = [%s]\n", cmd);
	if (!ft_strncmp(cmd, "exit\0", 5))
		env->exit = 1;
	else if (!ft_strncmp(cmd, "echo\0", 5))
		ft_echo(env);
	else if (!(ft_strncmp(cmd, "pwd\0", 4)))
		ft_pwd();
	else if (!(ft_strncmp(cmd, "cd\0", 3)))
		ft_cd(env);
    else if (!(ft_strncmp(cmd, "clear\0", 6)))
        ft_clear_screen(env);
	else if ((!(ft_strncmp(cmd, "export\0", 7))) && env->flags[1])
		ft_export(env);
	else if ((!(ft_strncmp(cmd, "export\0", 7))) && (!env->flags[1]))
		env_malloc(env);
	else if (!(ft_strcmp(cmd, "unset")))
		ft_unset(env);
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
		env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
		is_command(env->flags[0], env);
		env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
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
				env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
				is_command(env->flags[0], env);
				env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
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
	int		pid;


	env->av_pipe = split_pipes(env);
	// dprintf(2, "pipe[0] = {%s}\n", env->av_pipe[0]);
	// dprintf(2, "\n________split pipes fonctionne________\n");
	// int i = 0;
	// while (env->av_pipe[i])
	// {
		// dprintf(2, "pipe[%d] = {%s} taille {%zu}\n", i, env->av_pipe[i], ft_strlen(env->av_pipe[i]));
		// dprintf(2, "mon nom de file redirection{%s}\n", env->redir[env->x]);
		// i++;
	// }
	// dprintf(2, "______________________________________\n");
	// dprintf(2, "Il y a %d pipes selon i\n", i);
	ft_is_exit_here(env);
	env->x = 0;
	// dprintf(2, "Je vais rentrer dans le if pipe + 1 existe\n");
	if (env->av_pipe[env->x + 1]) // il y a des commandes a piper
	{
		dprintf(2, "la3\n");
		ft_pipe_is_cmd(env, -1);
	}
	else
	{
		env->flags = split_wh_sp(env->av_pipe[env->x]);
		if (is_builtin_no_pipe(env->flags[0], env)) //il faut fork que si c'est pas un buitin
		{
			if ((pid = fork()) < 0)
				exit(EXIT_FAILURE);
			if (pid == 0)
			{
				// dprintf(2, "la2\n");
				env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
				is_command(env->flags[0], env);
				env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
				exit (0);
			}
			waitpid(pid, 0, 0);
		}
		else
		{
			// dprintf(2, "la1\n");
			env->isred[env->x] > '0' ? set_fd_redirection(env) : 0;
			is_command(env->flags[0], env);
			env->isred[env->x] > '0' ? restore_fd_redirection(env) : 0;
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
