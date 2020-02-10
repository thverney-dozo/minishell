/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:03:14 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/10 16:35:29 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (ft_strlen(str));
	else
		return (i);
}

void		ft_save(t_env *env, t_var *var)
{
	env->first = var;
	while (var->next)
	{
		env->save = var;
		var = var->next;
	}
}

t_var		*ft_lstvar(t_env *env)
{
	t_var	*var;
	t_var	*new;
	int		i;
	int		save;

	i = 0;
	var = NULL;
	new = NULL;
	while (env->my_env[i])
	{
		save = ft_find_char(env->my_env[i], '=');
		if (!(new = ft_lstnewvar(env->my_env[i], save, env)))
			return (NULL);
		ft_lstaddvar(&var, new);
		i++;
	}
	ft_save(env, var);
	return (var);
}

void		ft_export2(char *str, t_env *env, t_var *new)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (!(new = ft_lstnewvar(str, i, env)))
				return ;
			if (i == ft_strlen(str) - 1)
				return ;
			if (ft_verif_var(new->name, env, new->value) == 0)
				ft_lstaddvar2(new, env);
			else
			{
				free(new->name);
				free(new->value);
				free(new);
			}
			return ;
		}
		i++;
	}
}

void		ft_export(char *str, t_env *env)
{
	size_t	i;
	char	**dest;
	t_var	*new;

	new = NULL;
	dest = ft_split(str, ' ');
	i = 0;
	while (dest[i])
	{
		ft_export2(dest[i], env, new);
		free(dest[i++]);
	}
	free(dest[i]);
	free(dest);
}
