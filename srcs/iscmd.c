/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/05 14:11:32 by anloubie         ###   ########.fr       */
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

void	ft_pipe_is_cmd(t_env *env, int i)
{
	char	*cmd;

	i++;
	while (env->arg[i] && (env->arg[i] == ';' || env->arg[i] < 33
	|| env->arg[i] == '|'))
		i++;
	if (!env->arg[i])
	{
		write(1, "Bonus not handled\n", 19);
		return ;
	}
	while ((cmd = ft_strchr(env->arg, '|')) != NULL)
	{
		cmd++;
		while (*cmd && *cmd < 33)
			cmd++;
		verify_cmd_pipe(cmd, 0, env);
		env->arg = cmd;
	}
	verify_cmd_pipe(env->arg, 1, env);
}

int		is_pipe_here(t_env *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env->arg[i] && env->arg[i] != '|' && env->arg[i] != ';')
		i++;
	if (env->arg[i] == '|')
	{
		ft_pipe_is_cmd(env, i);
		return (0);
	}
	return (1);
}
