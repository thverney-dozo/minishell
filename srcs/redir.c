/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:24:51 by antoine           #+#    #+#             */
/*   Updated: 2020/02/25 07:50:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		stock_file(char *str, int tmp, t_env *env, t_cmd *cmd)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	while (str[i] && str[i] > 32 && !nbslash(str, i, cmd)
	&& str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			cmd->wichquote = (str[i++] == 34 ? 34 : 39);
			while (str[i] && str[i] != cmd->wichquote)
				env->redir[tmp][j++] = str[i++];
		}
		else
			env->redir[tmp][j++] = str[i];
		i++;
	}
	env->redir[tmp][j] = '\0';
	return (i);
}

int		count_redir_file(char *str, int i, t_cmd *cmd)
{
	int tmp;

	tmp = 0;
	while (str[i] && str[i] > 32 && !nbslash(str, i, cmd)
	&& str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			cmd->wichquote = (str[i++] == 34 ? 34 : 39);
			while (str[i] && str[i] != cmd->wichquote)
			{
				tmp++;
				i++;
			}
		}
		else
			tmp++;
		i++;
	}
	return (tmp);
}

/*
**	isred	{1 == <}	{2 == >}	{3 == >>}
*/

void	ft_redir(t_env *env)
{
	if (env->isred[env->x] == '1')
		env->fd_red = open(env->redir[env->x]
		, O_RDONLY, 0644);
	else if (env->isred[env->x] == '2')
		env->fd_red = open(env->redir[env->x]
		, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (env->isred[env->x] == '3')
		env->fd_red = open(env->redir[env->x]
		, O_CREAT | O_WRONLY | O_APPEND, 0644);
}

void	set_fd_redirection(t_env *env)
{
	ft_redir(env);
	if (env->isred[env->x] == '1')
		dup2(env->fd_red, STDIN_FILENO);
	else if (env->isred[env->x] == '2')
		dup2(env->fd_red, STDOUT_FILENO);
	else if (env->isred[env->x] == '3')
		dup2(env->fd_red, STDOUT_FILENO);
}

void	restore_fd_redirection(t_env *env)
{
	close(env->fd_red);
	if (env->isred[env->x] == '1')
		dup2(STDOUT_FILENO, 0);
	else if (env->isred[env->x] == '2')
		dup2(STDIN_FILENO, 1);
	else if (env->isred[env->x] == '3')
		dup2(STDIN_FILENO, 1);
}
