/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:48:25 by thverney          #+#    #+#             */
/*   Updated: 2020/02/17 17:49:43 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_multi_line_quote_two_pipe(t_cmd *cmd, int i)
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
				return ;
		}
		else if (cmd->cpy[i] == '|' && !how_many_backslash(cmd->cpy, i, cmd))
			is_word(cmd, i);
		i++;
	}
}

void	is_multi_line_quote_pipe(t_cmd *cmd, int i)
{
	cmd->words = 1;
	is_multi_line_quote_two_pipe(cmd, i);
}

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
				if (line[i] == 34 && !how_many_backslash(line, i, cmd))
					break ;
				else if (line[i] == 92 && line[i + 1] == 92)
					i++;
				count++;
				i++;
			}
		}
		else if (line[i] == 39 && !how_many_backslash(line, i, cmd))
		{
			i++;
			while (line[i] && line[i] != 39)
			{
				i++;
				count++;
			}
		}
		else if (line[i] == '$' && !how_many_backslash(line, i, cmd))
		{
			i++;
			count += count_dollar(env, line + i);
			while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
			&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
			&& line[i] != '>')
				i++;
			i--;
		}
		else if (!how_many_backslash(line, i, cmd) && (line[i] == '>' || line[i] == '<'))
		{
			i++;
			(line[i] == '>' ? i++ : 0);
			i = next_none_space(line, i);
			env->count_redir = count_redir_file(line, i, cmd);
			i = next_space(line, i);
		}
		else if (line[i] == 92 && line[i + 1] == 92)
		{
			count++;
			i++;
		}
		else if (((line[i + 1] == '|' && line[i] < 33) || line[i] == '|')
		&& !how_many_backslash(line, i, cmd))
			break ;
		else
			count++;
		line[i] ? i++ : 0;
	}
	while (line[i - 1] && line[i - 1] < 33)
	{
		i--;
		count--;
	}
	//dprintf(2, "countchar pipe = [%d]\n", count);
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
	if (!(env->cpy_pipe = (char**)malloc(sizeof(char*) * (cmd->words + 1))))
		return (NULL);
	if (!(env->redir = (char**)malloc(sizeof(char*) * (cmd->words + 1))))
		return (NULL);
	i = 0;
	tmp = 0;
	while (tmp < cmd->words)
	{
		j = 0;
		env->isred[tmp] = '0';
		env->count = count_chars_pipes(cmd, line + i, env);
		//dprintf(2, "count du nb de char dans split pipe = [%d]\n", env->count);
		if (!(str[tmp] = (char*)malloc(sizeof(char) * (env->count + 1))))
			return (NULL);
		if (!(env->cpy_pipe[tmp] = (char*)malloc(sizeof(char) * (env->count + 1))))
			return (NULL);
		if (!(env->redir[tmp] = (char *)malloc(sizeof(char) * (env->count_redir + 1))))
			return (NULL);
		//dprintf(2, "env->count = {%d}\n", env->count);
		while (line[i] && line[i] < 33)
			i++;
		while (line[i])
		{
			//dprintf(2, "oups1 = {%d}, {%c}\n", i, line[i]);
			if (line[i] == 34 && !how_many_backslash(line, i, cmd))
			{
				cmd->wichquote = line[i];
				i++;
				if (line[i] && line[i] != cmd->wichquote)
				{
					while (line[i])
					{
						if (line[i] == 34 && !how_many_backslash(line, i, cmd))
							break ;
						else if (line[i] == 92 && line[i + 1] == 92)
						{
							str[tmp][j] = line[i];
							env->cpy_pipe[tmp][j] = '2';
							i++;
						}
						else
						{
							str[tmp][j] = line[i];
							env->cpy_pipe[tmp][j] = (line[i] == '\\' ? '0' : '2');
						}
						//dprintf(2, "oups 2= {%d}, {%c}\n", i, line[i]);
						j++;
						i++;
					}
				}
			}
			else if ((line[i] == 39) && !how_many_backslash(line, i, cmd))
			{
				cmd->wichquote = line[i];
				i++;
				if (line[i] && line[i] != cmd->wichquote)
				{
					while (line[i] && line[i] != cmd->wichquote)
					{
						//dprintf(2, "oups3 = {%d}, {%c}\n", i, line[i]);
						str[tmp][j] = line[i];
						env->cpy_pipe[tmp][j] = '2';
						j++;
						i++;
					}
				}
			}
			else if (line[i] == '$' && !how_many_backslash(line, i, cmd))
			{
				i++;
				j += ft_replace_word(env, line + i, &(str[tmp][j]), &(env->cpy_pipe[tmp][j]));	
				while (line[i] && line[i] > 32 && line[i] != '\\' && line[i] != '$'
				&& line[i] != 34 && line[i] != 39 && line[i] != '|' && line[i] != '<'
				&& line[i] != '>')
					i++;
				i--;
			}
			else if (!how_many_backslash(line, i, cmd) && (line[i] == '>' || line[i] == '<'))
			{
				env->isred[tmp] = (line[i] == '>' ? '2' : '1');
				i++;
				env->isred[tmp] = (line[i] == '>' ? '3' : env->isred[tmp]);
				(line[i] == '>' ? i++ : 0);
				i = next_none_space(line, i);
				i += stock_redir_file(line + i , tmp, env, cmd);
			}
			else if (line[i] == 92 && line[i + 1] == 92)
			{
				env->cpy_pipe[tmp][j] = '2';
				str[tmp][j] = line[i];
				i++;
				j++;
			}
			else if (line[i] == '|' && !how_many_backslash(line, i, cmd))
			{
				i++;
				break ;
			}
			else
			{
				//dprintf(2, "oups5 = {%d}, {%c}\n", i, line[i]);
				if (env->count > j)
				{
					//dprintf(2, "oups6 = {%d}, {%c}\n", i, line[i]);
					env->cpy_pipe[tmp][j] = (line[i] == '\\' ? '0' : '2');
					(line[i] < 33 ? env->cpy_pipe[tmp][j] = '1' : 0);
					str[tmp][j] = line[i];
					j++;
				}
			}
			line[i] ? i++ : 0;
		}
		//dprintf(2, "j = {%d}\n", j);
		str[tmp][j] = '\0';
		env->cpy_pipe[tmp][j] = '\0';
		//dprintf(2, "file name [%s]taille=[%zu]\n", env->redir, ft_strlen(env->redir));
		//dprintf(2, "MA CHAINE pipe [%s]taille=[%zu]\n", str[tmp], ft_strlen(str[tmp]));
		//dprintf(2, "MA CHAINE baskslash [%s]taille=[%zu]\n", env->cpy_pipe[tmp],
		// ft_strlen(env->cpy_pipe[tmp]));
		tmp++;
	}
	str[tmp] = 0;
	env->cpy_pipe[tmp] = 0;
	env->redir[tmp] = 0;
	return (str);
}

char	**split_pipes(t_env *env)
{
	t_cmd	*cmd;

	//dprintf(2, "Je suis rentré dans split_pipes\n");
	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->cpy = env->args[env->i];
	is_multi_line_quote_pipe(cmd, 0);
	if (!(env->isred = (char*)malloc(sizeof(char) * (cmd->words + 1))))
		return (NULL);
	//dprintf(2, "Nombre de pipe selon word = [%d]\n", cmd->words);
	return (split_parse_done_pipe(env, cmd->cpy, cmd));
}
