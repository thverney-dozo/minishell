/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:39:39 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 14:30:20 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		next_space(char *str, int i)
{
	while (str[i] && str[i] > 32)
		i++;
	return (i);
}

int		next_none_space(char *str, int i)
{
	while (str[i] && str[i] < 33)
		i++;
	return (i);
}

int		ft_error_syntax(t_env *env)
{
	write(2, "minishell : syntax error near unexpected token '", 49);
	ft_putchar_fd(env->copy_free[env->i], 2);
	write(2, "'\n", 3);
	free(env->copy_free);
	env->copy_free = NULL;
	return (1);
}

int		nbslash(char *str, int i)
{
	int backslash;

	if (i > 0)
		i--;
	else
		return (0);
	backslash = 0;
	while (str[i] == '\\')
	{
		backslash++;
		i--;
	}
	return (backslash % 2);
}

void	is_word(t_cmd *cmd, int i)
{
	i++;
	while (cmd->cpy[i] && cmd->cpy[i] < 33)
		i++;
	if (cmd->cpy[i])
		cmd->words++;
}
