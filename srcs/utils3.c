/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:55:11 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 05:06:14 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_cpy(t_env *env)
{
	free(env->copy_free);
	env->copy_free = NULL;
	return (1);
}

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
