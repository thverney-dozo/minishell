/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/08 04:24:51 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo_n(char *cmd, int j)
{
	int		i;
	int		tmp;
	char	*new;

	i = 0;
	j += 2;
	while (cmd[j] && cmd[j] < 33)
		j++;
	tmp = j;
	while (cmd[tmp] && cmd[tmp] != ';')
	{
		i++;
		tmp++;
	}
	new = ft_substr(cmd, j, i);
	write(1, new, ft_strlen(new));
}

void		ft_echo(char *cmd)
{
	char	*new;
	int		j;
	int		i;

	j = 5;
	i = 0;
	while (cmd[j] && cmd[j] < 33)
		j++;
	if (cmd[j] == '-' && cmd[j + 1] == 'n')
	{
		ft_echo_n(cmd, j);
		return ;
	}
	while (cmd[i] && cmd[i] != ';')
		i++;
	i -= 5;
	new = ft_substr(cmd, 5, i);
	write(1, new, ft_strlen(new));
	write(1, "\n", 1);
}
