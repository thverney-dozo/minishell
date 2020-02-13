/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/13 21:32:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_error(char *str)
{
	ft_putstr_fd("cd : No such file or directory : ", 1);
	ft_putendl_fd(str, 1);
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
		ft_putendl_fd("minishell : cd : HOME not found", 1);
		return ;
	}
	else if ((!(env->flags[1])) || (!(ft_strcmp(env->flags[1], "~"))))
		chdir(temp);
	else
		ret = chdir(env->flags[1]);
	if (ret == -1)
		ft_cd_error(env->flags[1]);
}
