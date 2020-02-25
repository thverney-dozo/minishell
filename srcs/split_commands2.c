/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:53:41 by thverney          #+#    #+#             */
/*   Updated: 2020/02/25 07:50:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_multi_line_quote_two(t_cmd *cmd, int i)
{
	while (cmd->cpy[i])
	{
		if ((cmd->cpy[i] == 39 || cmd->cpy[i] == 34)
		&& !nbslash(cmd->cpy, i, cmd))
		{
			cmd->wichquote = (cmd->cpy[i] == 34 ? 34 : 39);
			i++;
			while (cmd->cpy[i])
			{
				if (((cmd->cpy[i] == 34
				&& !nbslash(cmd->cpy, i, cmd))
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
		else if (cmd->cpy[i] == ';' && !nbslash(cmd->cpy, i, cmd))
			is_word(cmd, i);
		i++;
	}
}

void	is_valid_redir(t_cmd *cmd, int i)
{
	while (cmd->cpy[i])
	{
		if (!nbslash(cmd->cpy, i, cmd) && (cmd->cpy[i] == '>'
		|| cmd->cpy[i] == '<'))
		{
			i++;
			(cmd->cpy[i] == '>' ? i++ : 0);
			while (cmd->cpy[i] && cmd->cpy[i] < 33)
				i++;
			if (cmd->cpy[i] == '\0')
			{
				cmd->error = 2;
				return ;
			}
		}
		i++;
	}
}

int		is_multi_line_quote(t_cmd *cmd, int i)
{
	cmd->words = 1;
	is_valid_redir(cmd, 0);
	is_multi_line_quote_two(cmd, i);
	if (cmd->error == 1)
	{
		write(2, "multi line not handle (peer quote missing)\n", 44);
		free(cmd->cpy);
		cmd->cpy = NULL;
		return (0);
	}
	else if (cmd->error == 2)
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		free(cmd->cpy);
		cmd->cpy = NULL;
		return (0);
	}
	else
		return (1);
}
