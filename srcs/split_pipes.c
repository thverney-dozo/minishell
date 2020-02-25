/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:48:25 by thverney          #+#    #+#             */
/*   Updated: 2020/02/25 03:00:10 by thverney         ###   ########.fr       */
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
		if (line[i] == 34 && !how_many_backslash(line, i, cmd))
		{
			i++;
			while (line[i])
			{
				if (line[i] == '$' && !how_many_backslash(line, i, cmd)
				&& line[i + 1] != ' ' && line[i + 1] != '\\')
				{
					i++;
					count += count_dollar(env, line + i);
					while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
					&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
					&& line[i] != '>')
						i++;
				}
				if (line[i] == 34 && !how_many_backslash(line, i, cmd))
					break ;
				else if (line[i] == 92 && line[i + 1] == 92)
					i++;
				count++;
				i++;
			}
		}
		else if (line[i] == 39 && !how_many_backslash(line, i, cmd) && i++)
			while (line[i] && line[i] != 39 && i++)
				count++;
		else if (line[i] == '$' && !how_many_backslash(line, i, cmd) && i++)
		{
			count += count_dollar(env, line + i);
			while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
			&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
			&& line[i] != '>')
				i++;
		}
		else if (!how_many_backslash(line, i, cmd) && (line[i] == '>' || line[i] == '<'))
		{
			i++;
			(line[i] == '>' ? i++ : 0);
			i = next_none_space(line, i);
			env->count_redir = count_redir_file(line, i, cmd);
			i = next_space(line, i);
		}
		else if (line[i] == 92 && line[i + 1] == 92 && i++)
			count++;
		else if (((line[i + 1] == '|' && line[i] < 33) || line[i] == '|')
		&& !how_many_backslash(line, i, cmd))
			break ;
		else
			count++;
		line[i] ? i++ : 0;
	}
	while (line[i - 1] && line[i - 1] < 33 && !how_many_backslash(line, i - 1, cmd))
	{
		i--;
		count--;
	}
	return (count);
}

char	**split_parse_done_pipe(t_env *env, char *line, t_cmd *cmd)
{
	int		j;
	int		tmp;
	int		i;

	if (!(env->pipe[0] = (char**)malloc(sizeof(char*) * (cmd->words + 1)))
	|| (!(env->pipe[1] = (char**)malloc(sizeof(char*) * (cmd->words + 1)))))
		return (NULL);
	i = 0;
	tmp = 0;
	while (tmp < cmd->words)
	{
		j = 0;
		env->isred[tmp] = '0';
		env->count = count_chars_pipes(cmd, line + i, env);
		// dprintf(2, "count{%d}\n", env->count);
		if (!(env->pipe[0][tmp] = (char*)malloc(sizeof(char) * (env->count + 1)))
		|| (!(env->pipe[1][tmp] = (char*)malloc(sizeof(char) * (env->count + 1)))))
			return (NULL);

		while (line[i] && line[i] < 33)
			i++;
		while (line[i])
		{
			if (line[i] == 34 && !how_many_backslash(line, i, cmd))
			{
				cmd->wichquote = line[i++];
				if (line[i] && line[i] != cmd->wichquote)
				{
					while (line[i])
					{
						if (line[i] == 34 && !how_many_backslash(line, i, cmd))
							break ;
						if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\\'))
						{
							env->pipe[0][tmp][j] = line[i];
							env->pipe[1][tmp][j] = '2';
						}
						else if (line[i] == '$' && !how_many_backslash(line, i, cmd) && i++)
						{
							j += replace_word(env, line + i, &(env->pipe[0][tmp][j]), &(env->pipe[1][tmp][j])) - 1;	
							while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
							&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
							&& line[i] != '>')
								i++;
							i--;
						}
						else if (line[i] == 92 && line[i + 1] == 92)
						{
							env->pipe[1][tmp][j] = '2';
							env->pipe[0][tmp][j] = line[i++];
						}
						else
						{
							env->pipe[0][tmp][j] = line[i];
							env->pipe[1][tmp][j] = (line[i] == '\\' ? '0' : '2');
						}
						j++ && i++;
					}
				}
			}
			else if ((line[i] == 39) && !how_many_backslash(line, i, cmd))
			{
				cmd->wichquote = line[i++];
				if (line[i] && line[i] != cmd->wichquote)
				{
					while (line[i] && line[i] != cmd->wichquote)
					{
						env->pipe[1][tmp][j] = '2';
						env->pipe[0][tmp][j++] = line[i++];
					}
				}
			}
			else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\\'))
			{
				env->pipe[0][tmp][j] = line[i];
				env->pipe[1][tmp][j] = '2';
			}
			else if (line[i] == '$' && !how_many_backslash(line, i, cmd) && i++)
			{
				j += replace_word(env, line + i, &(env->pipe[0][tmp][j]), &(env->pipe[1][tmp][j]));	
				while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
				&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
				&& line[i] != '>')
					i++;
				i--;
			}
			else if (!how_many_backslash(line, i, cmd) && (line[i] == '>' || line[i] == '<'))
			{
				env->isred[tmp] = (line[i++] == '>' ? '2' : '1');
				env->isred[tmp] = (line[i] == '>' ? '3' : env->isred[tmp]);
				(line[i] == '>' ? i++ : 0);
				i = next_none_space(line, i);
				i += stock_file(line + i , tmp, env, cmd);
			}
			else if (line[i] == 92 && line[i + 1] == 92)
			{
				env->pipe[1][tmp][j] = '2';
				env->pipe[0][tmp][j++] = line[i++];
			}
			else if (line[i] == '|' && !how_many_backslash(line, i, cmd) && i++)
				break ;
			else
			{
				if (env->count > j)
				{
					env->pipe[1][tmp][j] = (line[i] == '\\' ? '0' : '2');
					(line[i] < 33 ? env->pipe[1][tmp][j] = '1' : 0);
					env->pipe[0][tmp][j] = line[i];
					j++;
				}
			}
			line[i] ? i++ : 0;
		}
		env->pipe[0][tmp][j] = '\0';
		env->pipe[1][tmp][j] = '\0';
		// dprintf(2, "len de 1{%zu}\n", ft_strlen(env->pipe[1][tmp]));
		// dprintf(2, "len de 0{%zu}\n", ft_strlen(env->pipe[0][tmp]));
		tmp++;
	}
	env->pipe[0][tmp] = 0;
	env->pipe[1][tmp] = 0;
	return (env->pipe[0]);
}

char	**split_pipes(t_env *env)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->cpy = env->args[env->i];
	is_multi_line_quote_pipe(cmd, 0);
	if (!(env->isred = (char*)malloc(sizeof(char) * (cmd->words + 1))))
		return (NULL);
	return (split_parse_done_pipe(env, cmd->cpy, cmd));
}
