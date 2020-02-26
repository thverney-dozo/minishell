/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:48:50 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 10:54:24 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_error(t_env *env)
{
	env->i = 0;
	if (!(env->copy_free[env->i]) || !(env->copy_free))
		return (1);
	while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
		env->i++;
	if ((env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
	&& (env->ret = 258))
		return (ft_error_syntax(env));
	while (env->copy_free[env->i])
	{
		if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
		{
			env->copy_free[env->i] ? env->i++ : 0;
			while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
				env->i++;
			if ((env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
			&& (env->ret = 258))
				return (ft_error_syntax(env));
		}
		env->i++;
	}
	return (0);
}

void	fill_triple_string(t_env *env, int j, char slash, char line)
{
	env->pipe[0][env->t][j] = line;
	env->pipe[1][env->t][j] = slash;
}

/*
** 92 = \   36 = $   34 = "   39 = '   124 = |   60 = <    62 = >
*/

int		is_forbidden_letter(char c)
{
	if (c && c > 32 && c != 92 && c != 36
	&& c != 34 && c != 39 && c != 124 && c != 60
	&& c != 62)
		return (1);
	return (0);
}

int		malloc_triple_tab(t_env *env, t_cmd *cmd)
{
	if (!(env->pipe[0] = (char**)malloc(sizeof(char*) * (cmd->words + 1)))
	|| (!(env->pipe[1] = (char**)malloc(sizeof(char*) * (cmd->words + 1)))))
		return (0);
	return (1);
}

int		malloc_tab(t_env *env)
{
	if (!(env->pipe[0][env->t] = (char*)malloc(sizeof(char) * (env->count + 1)))
	|| (!(env->pipe[1][env->t] = (char*)malloc(sizeof(char)
	* (env->count + 1)))))
		return (0);
	return (1);
}
