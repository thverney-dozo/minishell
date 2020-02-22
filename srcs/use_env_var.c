/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:26:55 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/22 19:48:50 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		replace_word_two(t_env *env, char *str, char *cpy, char *tmp)
{
	int		i;
	int		count;

	count = 0;
	while (env->var)
	{
		if (!(ft_strcmp(tmp, env->var->name)))
		{
			i = ft_strlen(env->var->value);
			while (count < i)
			{
				str[count] = env->var->value[count];
				cpy[count] = '2';
				count++;
			}
			free(tmp);
			env->var = env->first;
			return (count);
		}
		env->var = env->var->next;
	}
	free(tmp);
	env->var = env->first;
	return (0);
}

int		replace_word(t_env *env, char *line, char *str, char *cpy)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
	&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
	&& line[i] != '>')
		i++;
	tmp = ft_substr(line, 0, i);
	return (replace_word_two(env, str, cpy, tmp));
}

int		count_dollar(t_env *env, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] > 32 && str[i] != '\\' && str[i] != '$'
	&& str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i] != '<'
	&& str[i] != '>')
		i++;
	tmp = ft_substr(str, 0, i);
	while (env->var)
	{
		if (!(ft_strcmp(tmp, env->var->name)))
		{
			free(tmp);
			env->var = env->first;
			return (ft_strlen(env->var->value));
		}
		env->var = env->var->next;
	}
	free(tmp);
	env->var = env->first;
	return (0);
}
