/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/12 14:04:32 by anloubie         ###   ########.fr       */
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
	else if ((!(env->flags[1])) || (!(ft_strcmp(env->flags[1], "~"))))
		chdir(temp);
	else
		chdir(env->flags[1]);
}
