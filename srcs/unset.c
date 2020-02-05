/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:28:21 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/05 14:02:32 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unset_var(char *str, t_env *env)
{
	t_var	*save;

	save = NULL;
	while (env->var)
	{
		if (!(ft_strcmp(str, env->var->name)))
		{
			if (!(save))
				env->first = env->first->next;
			else
				save->next = env->var->next;
			free(env->var->value);
			free(env->var->name);
			free(env->var);
			break ;
		}
		else
			save = env->var;
		env->var = env->var->next;
	}
	env->var = env->first;
}

void		ft_unset(char *str, t_env *env)
{
	char	**dest;
	int		i;

	i = 1;
	dest = ft_split(str, ' ');
	if (!dest || !dest[1])
		return ;
	while (dest[i])
	{
		ft_unset_var(dest[i++], env);
		ft_save(env, env->var);
	}
}
