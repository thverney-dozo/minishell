/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:58:05 by thverney          #+#    #+#             */
/*   Updated: 2020/02/14 12:47:05 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_commands_no_quotes(t_cmd *cmd)
{
	return (ft_split(cmd->cpy, ';'));
}

int		how_many_backslash(char *str, int i, t_cmd *cmd)
{
	if (str[i - 1])
		i--;
	else
		return (0);
	cmd->backslash = 0;
	while (str[i] == '\\')
	{
		cmd->backslash++;
		i--;
	}
	return (cmd->backslash % 2);
}

char	*get_semi_coma(t_cmd *cmd, char *str, char c)
{
	int     i;

	i = 0;
	while (str[i] && (str[i] != c || how_many_backslash(str, i, cmd)))
		i++;
	cmd->index = i;
	if (str[i] == c)
		return (ft_substr(str, 0, i));
	else
		return (NULL);
}

void	is_word(t_cmd *cmd, int i)
{
	i++;
	while (cmd->cpy[i] && cmd->cpy[i] < 33)
		i++;
	if (cmd->cpy[i])
		cmd->words++;
}

void	is_multi_line_quote_two(t_cmd *cmd, int i)
{
	while (cmd->cpy[i])
	{
		if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34)
		&& !how_many_backslash(cmd->cpy, i, cmd))
		{
			cmd->wichquote = (cmd->cpy[i] == 34 ? 34 : 39);
			i++;
			while (cmd->cpy[i])
			{
				if (((cmd->cpy[i] == 34 && !how_many_backslash(cmd->cpy, i, cmd))
				|| cmd->cpy[i] == 39) && cmd->cpy[i] == cmd->wichquote)  
						break ;
				i++;
			}
			if (!(cmd->cpy[i]))
			{
				cmd->error = 1;	
				return ;
			}
		}
		else if (cmd->cpy[i] == ';' && !how_many_backslash(cmd->cpy, i, cmd))
			is_word(cmd, i);
		i++;
	}
}

int		is_multi_line_quote(t_cmd *cmd, int i)
{
	cmd->words = 1;
	is_multi_line_quote_two(cmd, i);
	if (cmd->error)
	{
		write(2, "multi line not handle (peer quote missing)\n", 44);
		free(cmd->cpy);
		cmd->cpy = NULL;
		return (0);
	}
	else
		return (1);
}

int		count_chars(t_cmd *cmd, char *line)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i] && line[i] < 33)
		i++;
	while (line[i])
	{
		if ((line[i] == 39 || line[i] == 34) && !how_many_backslash(line, i, cmd))
		{
			cmd->wichquote = (line[i] == 34 ? 34 : 39);
			count++;
			i++;
			while (line[i])
			{
				if (((line[i] == 34 && !how_many_backslash(line, i, cmd))
				|| line[i] == 39) && line[i] == cmd->wichquote)
					break ;
				count++;
				i++;
			}
			count++;
			i++;
		}
		else if (line[i] == ';' && !how_many_backslash(line, i, cmd))
			break ;
		count++;
		i++;
	}
	while (line[i - 1] && line[i - 1] < 33)
	{
		i--;
		count--;
	}
	return (count);
}

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
					str[tmp][j] = line[i];
					j++;
					i++;
				}
				str[tmp][j++] = line[i++];
			}
			else if (line[i] == ';' && !how_many_backslash(line, i, cmd))
			{
				i++;
				break ;
			}
			else
			{
				if (i <= env->count)
					str[tmp][j++] = line[i];
				i++;
			}
		}
		str[tmp][j] = '\0';
		tmp++;
	}
	str[tmp] = 0;
	return (str);
}

char	**split_commands(t_env *env)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->cpy = env->copy_free;
	// if (!ft_strchr(cmd->cpy, 39) && !ft_strchr(cmd->cpy, 34))
		// return (split_commands_no_quotes(cmd));
	cmd->error = 0;
	if (!is_multi_line_quote(cmd, 0))
		return (NULL);
	return (split_parse_done(env, cmd->cpy, cmd));
}
