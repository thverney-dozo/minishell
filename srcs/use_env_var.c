/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:26:55 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/14 13:37:59 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void		ft_replace_word(t_env *env, int i, int j)
{
	char	*tmp;

	while (env->var)
	{
		if (!(ft_strcmp(&(env->flags[i][j + 1]), env->var->name)))
		{
			tmp = env->flags[i];
			env->flags[i] = ft_strdup(env->var->value);
			free(tmp);
			env->var = env->first;
			return ;
		}
		env->var = env->var->next;
	}
	env->var = env->first;
}

void		ft_use_env_var(t_env *env)
{
	int		i;
	int		j;
	char	*tmp;
	int		index;

	i = 0;
	j = 0;
	while (env->flags[i])
	{
		index = get_index(env->flags[i], '$');
		if (!(tmp = ft_substr(env->flags[i], 0, index)))
			return ;
		j = 0;
		while (env->flags[i][j])
		{
			if (env->flags[i][j] == '$')
			{
				ft_replace_word(env, i, j);
				if (!(env->flags[i] = ft_strjoinfree(tmp, env->flags[i], 2)))
					return ;
			}
			j++;
		}
		i++;
	}
	ft_redir(env);
}
