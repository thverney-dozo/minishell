/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/05 23:33:41 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command(char *cmd, t_env *env)
{
	if (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "exit ", 5)
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
	else if (cmd[0])
		ft_not_found(cmd);
}

void	verify_cmd_pipe(char *cmd, int indic, t_env *env)
{
	if (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "exit ", 5)
	|| !ft_strncmp(cmd, "exit|", 5))
		indic ? exit(1) : 0;
	else if (!(ft_strncmp(cmd, "echo ", 5)) || !ft_strncmp(cmd, "echo", 5))
		indic ? ft_echo(cmd) : 0;
	else if (!(ft_strncmp(cmd, "pwd", 3)))
		indic ? ft_pwd(cmd, 3) : 0;
	else if (!(ft_strncmp(cmd, "cd", 2)))
		indic ? ft_cd(cmd + 3, env) : 0;
	else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
		indic ? ft_env(env) : 0;
	else
		ft_not_found(cmd);
}

void	ft_pipe_is_cmd(t_env *env)
{
	char *copy;


	if (!env->av_pipe[env->x + 1])
	{
		copy = env->av_pipe[env->x];
		while (*copy && *copy < 33)
			copy++;
		is_command(copy, env);
	}
	// verify_cmd_pipe(env->arg, 1, env);
}

void	is_pipe_here(t_env *env)
{
	int i;

	i = 0;
	if (ft_strchr(env->args[env->i], '|'))
	{
		env->av_pipe = ft_split(env->args[env->i], '|');
		env->copy_pipe = env->av_pipe;
		env->x = 0;
		while (env->av_pipe[env->x])
		{
			env->y = 0;
			while (env->av_pipe[env->x][env->y] < 33 && env->av_pipe[env->x][env->y])
				env->y++;
			ft_pipe_is_cmd(env);
			free(env->av_pipe[env->x]);
			env->av_pipe[env->x] = NULL;
			env->x++;
		}
		free(env->copy_pipe);
		env->copy_pipe = NULL;
	}
	else
		is_command(*env->args, env);
}
