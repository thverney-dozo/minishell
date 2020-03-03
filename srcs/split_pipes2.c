/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 01:02:17 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 13:12:48 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_multi_line_quote_two_pipe(t_cmd *cmd, int i)
{
	while (cmd->cpy[i])
	{
		if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34)
		&& !nbslash(cmd->cpy, i))
		{
			cmd->wichquote = (cmd->cpy[i] == 34 ? 34 : 39);
			i++;
			while (cmd->cpy[i])
			{
				if (((cmd->cpy[i] == 34
				&& !nbslash(cmd->cpy, i))
				|| cmd->cpy[i] == 39) && cmd->cpy[i] == cmd->wichquote)
					break ;
				i++;
			}
			if (!(cmd->cpy[i]))
				return ;
		}
		else if (cmd->cpy[i] == '|' && !nbslash(cmd->cpy, i))
			is_word(cmd, i);
		cmd->cpy[i] ? i++ : 0;
	}
}

void	is_multi_line_quote_pipe(t_cmd *cmd, int i)
{
	cmd->words = 1;
	is_multi_line_quote_two_pipe(cmd, i);
}

int		split_pipe_line_three(int i, t_env *env)
{
	if (env->line[i] == 92 && env->line[i + 1] == 92)
		fill_triple_string(env, env->j++, '2', env->line[i++]);
	else if (env->line[i] == '|' && !nbslash(env->line, i))
		return (i);
	else
	{
		if (env->count > env->j)
		{
			env->pipe[1][env->t][env->j] = (env->line[i] == '\\' ? '0' : '2');
			(env->line[i] < 33 ? env->pipe[1][env->t][env->j] = '1' : 0);
			env->pipe[0][env->t][env->j++] = env->line[i];
		}
	}
	return (i);
}

int		split_pipe_line_two(int i, t_env *env)
{
	if (env->line[i] == '$' && (env->line[i + 1] == ' '
	|| env->line[i + 1] == '\\'))
		fill_triple_string(env, env->j, '2', env->line[i]);
	else if (env->line[i] == '$' && !nbslash(env->line, i) && ++i)
	{
		env->j += replace_word(env, env->line + i,
		&(env->pipe[0][env->t][env->j]), &(env->pipe[1][env->t][env->j]));
		while (is_forbidden_letter(env->line[i]))
			i++;
		i--;
	}
	else if (!nbslash(env->line, i) && (env->line[i] == '>'
	|| env->line[i] == '<'))
	{
		env->isred[env->t] = (env->line[i++] == '>' ? '2' : '1');
		env->isred[env->t] = (env->line[i] == '>' ? '3' : env->isred[env->t]);
		(env->line[i] == '>' ? i++ : 0);
		i = next_none_space(env->line, i);
		i += stock_file(env->line + i, env->t, env);
	}
	else
		i = split_pipe_line_three(i, env);
	return (i);
}

int		split_pipe_dbquote(int i, t_env *env)
{
	if (env->line[i] == 34 && !nbslash(env->line, i))
		return (i);
	if (env->line[i] == '$' && (env->line[i + 1] == ' '
	|| env->line[i + 1] == '\\'))
		fill_triple_string(env, env->j, '2', env->line[i]);
	else if (env->line[i] == '$' && !nbslash(env->line, i) && i++)
	{
		env->j += replace_word(env, env->line + i,
		&(env->pipe[0][env->t][env->j]), &(env->pipe[1][env->t][env->j])) - 1;
		while (is_forbidden_letter(env->line[i]))
			i++;
		i--;
	}
	else if (env->line[i] == 92 && env->line[i + 1] == 92)
		fill_triple_string(env, env->j, '2', env->line[i++]);
	else
		fill_triple_string(env, env->j, (env->line[i] == '\\'
		? '0' : '2'), env->line[i]);
	env->j++ && i++;
	return (i);
}
