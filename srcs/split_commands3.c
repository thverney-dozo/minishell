/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:01:58 by thverney          #+#    #+#             */
/*   Updated: 2020/02/24 11:20:55 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		split_parse_two(int i, t_env *env, t_cmd *cmd, char **str)
{
	if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34)
	&& !how_many_backslash(cmd->cpy, i, cmd))
	{
		cmd->wichquote = (cmd->cpy[i] == 34 ? 34 : 39);
		str[env->y][env->j++] = cmd->cpy[i++];
		while (cmd->cpy[i] && i <= env->count)
		{
			if (((cmd->cpy[i] == 34 && !how_many_backslash(cmd->cpy, i, cmd))
			|| cmd->cpy[i] == 39) && cmd->cpy[i] == cmd->wichquote)
				break ;
			str[env->y][env->j++] = cmd->cpy[i++];
		}
		str[env->y][env->j++] = cmd->cpy[i++];
	}
	else if (cmd->cpy[i] == ';' && !how_many_backslash(cmd->cpy, i, cmd) && i++)
		return (-1);
	else
	{
		if (i <= env->count)
			str[env->y][env->j++] = cmd->cpy[i];
		i++;
	}
	return (i);
}

char	**split_parse(t_env *env, t_cmd *cmd, int i)
{
	char	**str;

	if (!(str = (char**)malloc(sizeof(char*) * (cmd->words + 1))))
		return (NULL);
	env->y = 0;
	while (env->y < cmd->words)
	{
		env->j = 0;
		env->count = count_chars(cmd, cmd->cpy + i);
		if (!(str[env->y] = (char*)malloc(sizeof(char) * (env->count + 1))))
			return (NULL);
		env->count += i;
		while (cmd->cpy[i] && cmd->cpy[i] < 33 && i <= env->count)
			i++;
		while (cmd->cpy[i])
		{
			i = split_parse_two(i, env, cmd, str);
			if (i == -1)
				break ;
		}
		str[env->y++][env->j] = '\0';
	}
	str[env->y] = 0;
	return (str);
}
