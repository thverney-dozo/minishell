/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:28:21 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/26 06:03:22 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unset_var(char *str, t_env *env)
{
	t_var	*save;

	save = NULL;
	while (env->var)
	{
		if (!(ft_strcmp(str, env->var->name)))
		{
			if (!(save))
				env->first = env->first->next;
			else
				save->next = env->var->next;
			ft_clear(&env->var->value);
			ft_clear(&env->var->name);
			free(env->var);
			break ;
		}
		else
			save = env->var;
		env->var = env->var->next;
	}
	env->var = env->first;
}

void		ft_unset(t_env *env)
{
	int		i;

	if (!env->flags[env->x][1])
		return ;
	i = 1;
	while (env->flags[env->x][i])
	{
		ft_unset_var(env->flags[env->x][i], env);
		ft_save(env, env->var);
		i++;
	}
}
