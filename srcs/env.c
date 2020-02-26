/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:55:10 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/26 04:47:41 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(t_env *env)
{
	while (env->var)
	{
		ft_putstr_fd(env->var->name, env->fd_red);
		write(1, "=", 1);
		ft_putendl_fd(env->var->value, env->fd_red);
		env->var = env->var->next;
	}
	env->var = env->first;
}
