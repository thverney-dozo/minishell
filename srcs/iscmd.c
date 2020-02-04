/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/04 04:44:58 by thverney         ###   ########.fr       */
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
		ft_pwd(cmd, 4);
	else if (!(ft_strncmp(cmd, "cd", 2)))
		ft_cd(cmd + 3);
	else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
		ft_env(env);
	else if (cmd[0] != '\0')
		ft_not_found(cmd);
}

void	verify_cmd_pipe(char *cmd, int indic, t_env *env)
{
	if (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "exit ", 5)
	|| !ft_strncmp(cmd, "exit|", 5))
		indic == 1 ? exit(1) : 0;
	else if (!(ft_strncmp(cmd, "echo ", 5)) || !ft_strncmp(cmd, "echo", 5))
		indic == 1 ? ft_echo(cmd) : 0;
	else if (!(ft_strncmp(cmd, "pwd", 3)))
		indic == 1 ? ft_pwd(cmd, 4) : 0;
	else if (!(ft_strncmp(cmd, "cd", 2)))
		indic == 1 ? ft_cd(cmd + 3) : 0;
	else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
		indic == 1 ? ft_env(env) : 0;
	else
		ft_not_found(cmd);
}

void	ft_pipe_is_cmd(t_env *env, int i)
{
	char	*cmd;

	i++;
	while (env->pos_prev[i] != '\0' && (env->pos_prev[i] == ';'
	|| env->pos_prev[i] < 33 || env->pos_prev[i] == '|'))
		i++;
	if (env->pos_prev[i] == '\0')
	{
		write(1, "Bonus not handled\n", 19);
		return ;
	}
	while ((cmd = ft_strchr(env->pos_prev, '|')) != NULL)
	{
		cmd++;
		while (*cmd != '\0' && *cmd < 33)
			cmd++;
		verify_cmd_pipe(cmd, 0, env);
		env->pos_prev = cmd;
	}
	verify_cmd_pipe(env->pos_prev, 1, env);
}

int		is_pipe_here(t_env *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env->pos_prev[i] != '\0' && env->pos_prev[i] != '|'
	&& env->pos_prev[i] != ';')
		i++;
	if (env->pos_prev[i] == '|')
	{
		ft_pipe_is_cmd(env, i);
		return (0);
	}
	return (1);
}
