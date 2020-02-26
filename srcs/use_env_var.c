/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:26:55 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/26 10:48:38 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		try_question_mark(t_env *env, char *str, char *cpy, char *tmp)
{
	int		i;
	char	*nb;
	int		len;

	if (!(ft_strcmp(tmp, "?")))
	{
		i = 0;
		nb = ft_itoa(env->ret);
		// dprintf(2, "tmp {%s}", nb);
		len = ft_strlen(nb);
		while (i < len)
		{
			str[i] = nb[i];
			cpy[i] = '2';
			i++;
		}
		free(nb);
		nb = NULL;
		return (i);
	}
	return (0);
}

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
	// dprintf(2, "LA== {%s}\n", tmp);
	i = try_question_mark(env, str, cpy, tmp);
	free(tmp);
	env->var = env->first;
	return (i);
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

int		try_question_mark_count(t_env *env, char *tmp)
{
	int		len;
	char	*nb;

	if (!(ft_strcmp(tmp, "?")))
	{
		nb = ft_itoa(env->ret);
		len = ft_strlen(nb);
		free(nb);
		nb = NULL;
		return (len);
	}
	return (0);
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
	i = try_question_mark_count(env, tmp);
	free(tmp);
	env->var = env->first;
	return (i);
}
