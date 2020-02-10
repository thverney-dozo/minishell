/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:58:05 by thverney          #+#    #+#             */
/*   Updated: 2020/02/10 12:04:39 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	**split_commands_no_quotes(t_cmd *cmd)
{
	return (ft_split(cmd->cpy, ';'));
}

char	*get_semi_coma(t_cmd *cmd, char *str, char c)
{
	int     i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	cmd->index = i;
	// dprintf(2, "index|%d|\n", cmd->index);
	// printf("MA CHAINE|%s|\n", ft_substr(str, 0, i));
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
		if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34) && cmd->cpy[i - 1] != '\\')
		{
			if (get_semi_coma(cmd, cmd->cpy + i + 1, cmd->cpy[i]) == NULL)
			{
				cmd->error = 1;	
				return ;
			}
			i+= cmd->index + 1;
		}
		else if (cmd->cpy[i] == ';' && cmd->cpy[i - 1] != '\\')
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
		write(1, "multi line not handle (peer quote missing)\n", 44);
		free(cmd->cpy);
		cmd->cpy = NULL;
		return (0);
	}
	else
		return (1);
}

int		count_chars(t_cmd *cmd, char *line, t_env *env)
{
	int i;
	int count;
	int		max;

	max = ft_strlen(line);
	count = 0;
	i = 0;
	while (line[i] && line[i] < 33)
		i++;
	while (line[i] && max--)
	{
		if ((line[i] == 39 || line[i] == 34) && line[i - 1] != '\\')
		{
			get_semi_coma(cmd, line + i + 1, line[i]);
			count += cmd->index;
			i += cmd->index + 1;
		}
		else if (line[i + 1] == ';' && line[i] != '\\')
			break ;
		else
			count++;
		i++;

	}
	env->i = i;
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
		env->count = count_chars(cmd, line + i, env);
		if (!(str[j] = (char*)malloc(sizeof(char) * (env->count + 1))))
			return (NULL);
		while (line[i] && line[i] < 33)
			i++;
		while (line[i])
		{
			if ((line[i] == 39 || line[i] == 34) && line[i - 1] != '\\')
			{
				cmd->wichquote = line[i];
				i++;
				while (line[i] && line[i] != cmd->wichquote)
					str[tmp][j++] = line[i++];
			}
			else if (line[i + 1] == ';' && line[i] != '\\')
				break ;
			else
				str[tmp][j++] = line[i++];
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
	if (!ft_strchr(cmd->cpy, 39) && !ft_strchr(cmd->cpy, 34))
		return (split_commands_no_quotes(cmd));
	cmd->error = 0;
	if (!is_multi_line_quote(cmd, 0))
		return (NULL);
	return (split_parse_done(env, cmd->cpy, cmd));
}
