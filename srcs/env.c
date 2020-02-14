/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:55:10 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/14 12:40:39 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(t_env *env)
{
	while (env->var)
	{
		ft_putstr_fd(env->var->name, env->fd);
		write(env->fd, "=", 1);
		ft_putendl_fd(env->var->value, env->fd);
		env->var = env->var->next;
	}
	env->var = env->first;
}
