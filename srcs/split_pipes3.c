/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:40:11 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 04:16:49 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_chars_pipes_three(char *line, t_env *env, int i)
{
	if (line[i] == '$' && !nbslash(line, i) && i++)
	{
		env->count += count_dollar(env, line + i);
		while (is_forbidden_letter(line[i]))
			i++;
	}
	else if (!nbslash(line, i) && (line[i] == '>'
	|| line[i] == '<') && i++)
	{
		(line[i] == '>' ? i++ : 0);
		i = next_none_space(line, i);
		env->count_char_redir = count_redir_file(line, i);
		i = next_space(line, i);
	}
	else if (line[i] == 92 && line[i + 1] == 92 && i++)
		env->count++;
	else if (((line[i + 1] == '|' && line[i] < 33) || line[i] == '|')
	&& !nbslash(line, i))
		return (i);
	else
		env->count++;
	return (i);
}

int		count_chars_pipes_two(char *line, t_env *env, int i)
{
	if (line[i] == 34 && !nbslash(line, i) && i++)
	{
		while (line[i])
		{
			if (line[i] == '$' && !nbslash(line, i)
			&& line[i + 1] != ' ' && line[i + 1] != '\\' && i++)
			{
				env->count += count_dollar(env, line + i);
				while (is_forbidden_letter(line[i]))
					i++;
			}
			if (line[i] == 34 && !nbslash(line, i))
				break ;
			else if (line[i] == 92 && line[i + 1] == 92)
				i++;
			env->count++ && i++;
		}
	}
	else if (line[i] == 39 && !nbslash(line, i) && i++)
		while (line[i] && line[i] != 39 && i++)
			env->count++;
	else
		i = count_chars_pipes_three(line, env, i);
	return (i);
}

void	count_chars_pipes(char *line, t_env *env, int i)
{
	env->count = 0;
	while (line[i] && line[i] < 33)
		i++;
	while (line[i])
	{
		i = count_chars_pipes_two(line, env, i);
		if (((line[i + 1] == '|' && line[i] < 33) || line[i] == '|')
		&& !nbslash(line, i))
			break ;
		line[i] ? i++ : 0;
	}
	while (!nbslash(line, i - 1) && line[i - 1]
	&& line[i - 1] < 33 && i--)
		env->count--;
}
