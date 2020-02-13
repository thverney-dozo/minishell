/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/13 17:57:46 by aeoithd          ###   ########.fr       */
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
		ft_putendl_fd("minishell : cd : HOME not found", 2);
		return ;
	}
	else if ((!(env->flags[1])) || (!(ft_strcmp(env->flags[1], "~"))))
		chdir(temp);
	else if (chdir(env->flags[1]) == -1)
	{
		write(2, "minishell: cd : ", 16);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}
