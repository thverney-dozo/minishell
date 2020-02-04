/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_found.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:58:31 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/03 17:34:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_not_found(char *cmd)
{
	int i;

	i = 0;
	while (*cmd < 33 && *cmd != '\0')
		cmd++;
	if (*cmd != '\0')
	{
		write(1, "minishell: command not found: ", 30);
		while (cmd[i] > 32)
			i++;
		write(1, cmd, i);
		write(1, "\n", 1);
	}
}
