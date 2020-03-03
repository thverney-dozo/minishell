/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:03:41 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 07:48:00 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	how_many_redir(t_env *env)
{
	int	i;

	i = 0;
	while (env->copy_free[i])
	{
		if ((env->copy_free[i] == '>' || env->copy_free[i] == '<')
		&& !nbslash(env->copy_free, i))
			env->count_redir++;
		i++;
		if (env->copy_free[i] == '>' || env->copy_free[i] == '<')
			i++;
	}
}

int		free_syntax_error(t_env *env)
{
	ft_clear(&env->copy_free);
	return (1);
}

int		blank_line(t_env *env)
{
	int i;

	i = 0;
	while (env->copy_free[i])
	{
		if (env->copy_free[i] > 32)
			break ;
		i++;
	}
	if (env->copy_free[i])
		return (0);
	else
	{
		ft_clear(&env->copy_free);
		return (1);
	}
}

void	free_args(t_env *env)
{
	env->i = 0;
	while (env->args[env->i])
	{
		free(env->args[env->i]);
		env->args[env->i] = NULL;
		env->i++;
	}
	free(env->args);
	env->args = NULL;
}

void	join_gnl_loop(t_env *env)
{
	if (env->join)
	{
		free(env->join);
		env->join = ft_strdup(env->copy_free);
		free(env->copy_free);
		env->copy_free = NULL;
	}
	else
		env->join = NULL;
}
