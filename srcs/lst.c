/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:25:01 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/13 21:06:24 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_env(t_env *env)
{
	int		count;

	count = 0;
	while (env->var)
	{
		count++;
		env->var = env->var->next;
	}
	env->var = env->first;
	return (count);
}

int		ft_verif_var(char *name, t_env *env, char *value)
{
	while (env->var)
	{
		if (!(ft_strcmp(name, env->var->name)))
		{
			free(env->var->value);
			if (!(env->var->value = ft_strdup(value)))
				return (-1);
			env->var = env->first;
			return (1);
		}
		env->var = env->var->next;
	}
	env->var = env->first;
	return (0);
}

void	ft_lstaddvar2(t_var *new, t_env *env)
{
	new->next = env->save->next;
	env->save->next = new;
	env->save = env->save->next;
}

void	ft_lstaddvar(t_var **alst, t_var *new)
{
	t_var	*temp;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}

t_var	*ft_lstnewvar(char *str, int i, t_env *env)
{
	t_var	*var;
	char	*name;
	char	*value;

	if (!(name = ft_substr(str, 0, i)))
		return (NULL);
	if (!(value = ft_substr(str, i + 1, ft_strlen(str))))
		return (NULL);
	if (!(var = (t_var*)malloc(sizeof(t_var))))
		return (NULL);
	if (!(var->name = ft_strdup(name)))
		return (NULL);
	free(name);
	if (!(var->value = ft_strdup(value)))
		return (NULL);
	free(value);
	var->next = NULL;
	if (!ft_strcmp(var->name, "PATH\0"))
		env->path = ft_split(var->value, ':');
	return (var);
}
