/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/08 22:00:55 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_home(t_env *env)
{
	while (env->var)
	{
		if (!(ft_strcmp("HOME", env->var->name)))
			return (env->var->value);
		env->var = env->var->next;
	}
	env->var = env->first;
	return (NULL);
}

void	ft_cd(t_env *env)
{
	char	*temp;

	temp = ft_get_home(env);
	env->var = env->first;
	if (!temp)
	{
		ft_putendl_fd("minishell : cd : HOME not found", 1);
		return ;
	}
	else if (!(ft_strcmp(env->flags[1], "~")))
		chdir(temp);
	else
		chdir(env->flags[1]);
}
