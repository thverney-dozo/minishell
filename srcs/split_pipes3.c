/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:40:11 by thverney          #+#    #+#             */
/*   Updated: 2020/02/25 07:50:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_chars_pipes(t_cmd *cmd, char *line, t_env *env)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i] && line[i] < 33)
		i++;
	while (line[i])
	{
		if (line[i] == 34 && !nbslash(line, i, cmd) && i++)
		{
			while (line[i])
			{
				if (line[i] == '$' && !nbslash(line, i, cmd)
				&& line[i + 1] != ' ' && line[i + 1] != '\\' && i++)
				{
					count += count_dollar(env, line + i);
					while (is_forbidden_letter(line[i]))
						i++;
				}
				if (line[i] == 34 && !nbslash(line, i, cmd))
					break ;
				else if (line[i] == 92 && line[i + 1] == 92)
					i++;
				count++ && i++;
			}
		}
		else if (line[i] == 39 && !nbslash(line, i, cmd) && i++)
			while (line[i] && line[i] != 39 && i++)
				count++;
		else if (line[i] == '$' && !nbslash(line, i, cmd) && i++)
		{
			count += count_dollar(env, line + i);
			while (is_forbidden_letter(line[i]))
				i++;
		}
		else if (!nbslash(line, i, cmd) && (line[i] == '>'
		|| line[i] == '<') && i++)
		{
			(line[i] == '>' ? i++ : 0);
			i = next_none_space(line, i);
			env->count_redir = count_redir_file(line, i, cmd);
			i = next_space(line, i);
		}
		else if (line[i] == 92 && line[i + 1] == 92 && i++)
			count++;
		else if (((line[i + 1] == '|' && line[i] < 33) || line[i] == '|')
		&& !nbslash(line, i, cmd))
			break ;
		else
			count++;
		line[i] ? i++ : 0;
	}
	while (!nbslash(line, i - 1, cmd) && line[i - 1]
	&& line[i - 1] < 33 && i--)
		count--;
	return (count);
}
