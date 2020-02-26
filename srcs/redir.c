/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:24:51 by antoine           #+#    #+#             */
/*   Updated: 2020/02/26 05:10:20 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		stock_file(char *str, int tmp, t_env *env)
{
	int	j;
	int i;
	int	wichquote;

	wichquote = 0;
	j = 0;
	i = 0;
	if (!(env->redir[tmp] = malloc(sizeof(char) * (env->count_char_redir + 1))))
		return (-1);
	while (str[i] && str[i] > 32 && !nbslash(str, i)
	&& str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			wichquote = (str[i++] == 34 ? 34 : 39);
			while (str[i] && str[i] != wichquote)
				env->redir[tmp][j++] = str[i++];
		}
		else
			env->redir[tmp][j++] = str[i];
		i++;
	}
	env->redir[tmp][j] = '\0';
	return (i);
}

int		count_redir_file(char *str, int i)
{
	int tmp;
	int	wichquote;

	wichquote = 0;
	tmp = 0;
	while (str[i] && str[i] > 32 && !nbslash(str, i)
	&& str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			wichquote = (str[i++] == 34 ? 34 : 39);
			while (str[i] && str[i] != wichquote)
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
	free(env->redir[env->x]);
	env->redir[env->x] = NULL;
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
