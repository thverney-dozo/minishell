/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_found.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:58:31 by anloubie          #+#    #+#             */
/*   Updated: 2020/03/03 04:42:26 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_not_found(char *cmd, t_env *env)
{
	int i;

	i = 0;
	while (*cmd < 33 && *cmd)
		cmd++;
	if (*cmd)
	{
		write(2, "minishell: command not found: ", 30);
		while (cmd[i] > 32)
			i++;
		write(2, cmd, i);
		write(2, "\n", 1);
	}
	env->ret = 127;
}
