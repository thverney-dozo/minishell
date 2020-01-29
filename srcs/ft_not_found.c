/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_found.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:58:31 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/29 11:48:02 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_not_found(char *cmd)
{
	int i;

	i = 0;
	write(1, "minishell: command not found: ", 30);
	while (*cmd < 33)
		cmd++;
	while (cmd[i] > 32)
		i++;
	cmd[i] = '\0';
	write(1, cmd, ft_strlen(cmd));
	write(1, "\n", 1);
}
