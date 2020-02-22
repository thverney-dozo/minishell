/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:01:58 by thverney          #+#    #+#             */
/*   Updated: 2020/02/22 20:26:06 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_parse_done(t_env *env, char *line, t_cmd *cmd)
{
	char	**str;
	int		j;
	int		tmp;
	int		i;

	if (!(str = (char**)malloc(sizeof(char*) * (cmd->words + 1))))
		return (NULL);
	i = 0;
	tmp = 0;
	while (tmp < cmd->words)
	{
		j = 0;
		env->count = count_chars(cmd, line + i);
		if (!(str[tmp] = (char*)malloc(sizeof(char) * (env->count + 1))))
			return (NULL);
		env->count += i;
		while (line[i] && line[i] < 33 && i <= env->count)
			i++;
		while (line[i])
		{
			if ((line[i] == 39 || line[i] == 34)
			&& !how_many_backslash(line, i, cmd))
			{
				cmd->wichquote = (line[i] == 34 ? 34 : 39);
				str[tmp][j++] = line[i++];
				while (line[i] && i <= env->count)
				{
					if (((line[i] == 34 && !how_many_backslash(line, i, cmd))
					|| line[i] == 39) && line[i] == cmd->wichquote)
						break ;
					str[tmp][j++] = line[i++];
				}
				str[tmp][j++] = line[i++];
			}
			else if (line[i] == ';' && !how_many_backslash(line, i, cmd) && i++)
				break ;
			else
			{
				if (i <= env->count)
					str[tmp][j++] = line[i];
				i++;
			}
		}
		str[tmp++][j] = '\0';
	}
	str[tmp] = 0;
	return (str);
}
