/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:55:10 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/04 09:10:39 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(t_env *env)
{
	while (env->var)
	{
		write(1, env->var->name, ft_strlen(env->var->name));
		write(1, "=", 1);
		write(1, env->var->value, ft_strlen(env->var->value));
		write(1, "\n", 1);
		if (env->var->next)
			env->var = env->var->next;
		else
			break ;
	}
	env->var = env->first;
}
