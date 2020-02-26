/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/26 13:56:20 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_error(char *str, t_env *env)
{
	ft_putstr_fd("cd : No such file or directory : ", 2);
	ft_putendl_fd(str, 2);
	env->ret = 1;
}

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
	int		ret;

	ret = 0;
	temp = ft_get_home(env);
	env->var = env->first;
	if (!temp)
	{
		ft_putendl_fd("minishell : cd : HOME not found", 2);
		return ;
	}
	else if ((!(env->flags[env->x][1]))
	|| (!(ft_strcmp(env->flags[env->x][1], "~"))))
		env->ret = chdir(temp);
	else
		ret = chdir(env->flags[env->x][1]);
	if (ret == -1)
		ft_cd_error(env->flags[env->x][1], env);
}
