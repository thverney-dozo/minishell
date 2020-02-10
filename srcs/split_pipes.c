/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:48:25 by thverney          #+#    #+#             */
/*   Updated: 2020/02/10 20:29:22 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_pipes_no_quotes(t_cmd *cmd)
{
	return (ft_split(cmd->cpy, '|'));
}

void	is_multi_line_quote_two_pipes(t_cmd *cmd, int i)
{
	while (cmd->cpy[i])
	{
		if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34)
		&& !how_many_backslash(cmd->cpy, i, cmd))
		{
			if (get_semi_coma(cmd, cmd->cpy + i + 1, cmd->cpy[i]) == NULL)
			{
				cmd->error = 1;	
				return ;
			}
			i+= cmd->index + 1;
		}
		else if (cmd->cpy[i] == '|' && !how_many_backslash(cmd->cpy, i, cmd))
			is_word(cmd, i);
		i++;
	}
}

int		is_multi_line_quote_pipes(t_cmd *cmd, int i)
{
	cmd->words = 1;
	is_multi_line_quote_two_pipes(cmd, i);
	if (cmd->error)
	{
		write(1, "multi line not handle (peer quote missing)\n", 44);
		free(cmd->cpy);
		cmd->cpy = NULL;
		return (0);
	}
	else
		return (1);
}

int		count_chars_pipes(t_cmd *cmd, char *line, t_env *env)
{
	int i;
	int count;

	env->max = ft_strlen(line);
	count = 0;
	i = 0;
	while (line[i] && line[i] < 33)
		i++;
	while (line[i] && env->max--)
	{
		if ((line[i] == 39 || line[i] == 34) && !how_many_backslash(line, i, cmd))
		{
			get_semi_coma(cmd, line + i + 1, line[i]);
			count += cmd->index + 1;
			i += cmd->index + 1;
		}
		else if (line[i + 1] == '|' && !how_many_backslash(line, i, cmd))
			break ;
		else
			count++;
		i++;

	}
	while (line[i - 1] && line[i - 1] < 33)
	{
		i--;
		count--;
	}
	// env->i = i;
	env->max = ft_strlen(line);
	return (count);
}

char	**split_parse_done_pipe(t_env *env, char *line, t_cmd *cmd)
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
		env->count = count_chars_pipes(cmd, line + i, env);
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
				i++;
				while (line[i] && line[i] != cmd->wichquote && i <= env->count
				&& !how_many_backslash(line, i, cmd))
				{
					str[tmp][j] = line[i];
					j++;
					i++;
				}
			}
			else if (line[i] == '|' && !how_many_backslash(line, i - 1, cmd))
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

char	**split_pipes(t_env *env)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->cpy = env->args[env->i];
	if (!ft_strchr(cmd->cpy, 39) && !ft_strchr(cmd->cpy, 34))
		return (split_pipes_no_quotes(cmd));
	cmd->error = 0;
	if (!is_multi_line_quote_pipes(cmd, 0))
		return (NULL);
	return (split_parse_done_pipe(env, cmd->cpy, cmd));
}
