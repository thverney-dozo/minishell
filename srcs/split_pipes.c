/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:48:25 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 03:23:45 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		split_pipe_line(int i, t_env *env, t_cmd *cmd)
{
	if (env->line[i] == 34 && !nbslash(env->line, i))
	{
		cmd->wichquote = env->line[i++];
		if (env->line[i] && env->line[i] != cmd->wichquote)
		{
			while (env->line[i] && !(env->line[i] == 34
			&& !nbslash(env->line, i)))
				i = split_pipe_dbquote(i, env);
		}
	}
	else if ((env->line[i] == 39) && !nbslash(env->line, i))
	{
		cmd->wichquote = env->line[i++];
		if (env->line[i] && env->line[i] != cmd->wichquote)
			while (env->line[i] && env->line[i] != cmd->wichquote)
				fill_triple_string(env, env->j++, '2', env->line[i++]);
	}
	else
		i = split_pipe_line_two(i, env);
	env->line[i] ? i++ : 0;
	return (i);
}

char	**split_parse_pipe(t_env *env, t_cmd *cmd, int i)
{
	if (!(malloc_triple_tab(env, cmd)))
		return (NULL);
	while (env->t < cmd->words)
	{
		env->j = 0;
		env->isred[env->t] = '0';
		count_chars_pipes(env->line + i, env, 0);
		if (!(malloc_tab(env)))
			return (NULL);
		while (env->line[i] && env->line[i] < 33)
			i++;
		while (env->line[i] && !(env->line[i] == '|'
		&& !nbslash(env->line, i)))
			i = split_pipe_line(i, env, cmd);
		if (env->line[i] == '|' && !nbslash(env->line, i))
			i++;
		fill_triple_string(env, env->j, '\0', '\0');
		env->t++;
	}
	env->pipe[0][env->t] = 0;
	env->pipe[1][env->t] = 0;
	free(cmd);
	cmd = NULL;
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
	env->line = cmd->cpy;
	env->t = 0;
	return (split_parse_pipe(env, cmd, 0));
}
