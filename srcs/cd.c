/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/06 14:37:08 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_two(char *tmp, char *path, int i)
{
	while (*path < 33 && *path)
		path++;
	tmp = path;
	i = 0;
	while (*tmp > 32 && *tmp++)
		i++;
	while (*tmp < 33 && *tmp && *tmp != ';' && *tmp != '|')
		tmp++;
	if (*tmp && *tmp != ';' && *tmp != '|')
	{
		write(1, "cd: string not in pwd: ", 23);
		write(1, path, i);
		write(1, "\n", 1);
	}
	else
		chdir(path);
}

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

void	ft_cd(char *path, t_env *env)
{
	char	*tmp;
	char	*temp;

	tmp = path;
	temp = ft_get_home(env);
	env->var = env->first;
	while (*tmp < 33 && *tmp && *tmp != ';' && *tmp != '|')
		tmp++;
	if (!*tmp || *tmp == ';' || *tmp == '|')
	{
		if (!temp)
		{
			ft_putendl_fd("minishell : cd : HOME not found", 1);
			return ;
		}
		chdir(temp);
	}
	else if (!(ft_strcmp(path, "~")))
		chdir(temp);
	else
		ft_cd_two(tmp, path, 0);
}
