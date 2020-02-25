/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:48:50 by thverney          #+#    #+#             */
/*   Updated: 2020/02/25 04:49:00 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_error(t_env *env)
{
	env->i = 0;
	if (!(env->copy_free[env->i]) || !(env->copy_free))
		return (1);
	env->ret = 0;
	while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
		env->i++;
	if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
		return (ft_error_syntax(env));
	while (env->copy_free[env->i])
	{
		if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
		{
			env->copy_free[env->i] ? env->i++ : 0;
			while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
				env->i++;
			if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
				return (ft_error_syntax(env));
		}
		env->i++;
	}
	return (0);
}
