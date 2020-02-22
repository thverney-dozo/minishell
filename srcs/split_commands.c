/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:58:05 by thverney          #+#    #+#             */
/*   Updated: 2020/02/22 20:24:41 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_chars_two(t_cmd *cmd, char *line, int i, int count)
{
	while (line[i])
	{
		if ((line[i] == 39 || line[i] == 34)
		&& !how_many_backslash(line, i, cmd))
		{
			cmd->wichquote = (line[i] == 34 ? 34 : 39);
			i++ && count++;
			while (line[i])
			{
				if (((line[i] == 34 && !how_many_backslash(line, i, cmd))
				|| line[i] == 39) && line[i] == cmd->wichquote)
					break ;
				i++ && count++;
			}
			i++ && count++;
		}
		else if (line[i] == ';' && !how_many_backslash(line, i, cmd))
			break ;
		i++ && count++;
	}
	while (line[i - 1] && line[i - 1] < 33)
		i-- && count--;
	return (count);
}

int		count_chars(t_cmd *cmd, char *line)
{
	int i;
	int count;

	count = 0;
	i = next_none_space(line, 0);
	count = count_chars_two(cmd, line, i, count);
	return (count);
}

char	**split_commands(t_env *env)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->cpy = env->copy_free;
	cmd->error = 0;
	if (!is_multi_line_quote(cmd, 0))
		return (NULL);
	return (split_parse_done(env, cmd->cpy, cmd));
}
