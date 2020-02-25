/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:41:17 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/25 03:52:39 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_sig_kill(int sig_id)
{
	char	buf[PATH_MAX + 1];
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	(void)sig_id;
	ft_putstr_fd("\b \b\b \b", 2);
	ft_putstr_fd("\n", 1);
	write(1, "\033[31m<#\033[34m(", 14);
	getcwd(buf, PATH_MAX);
	while (buf[i] >= 32)
		i++;
	while (buf[i] != '/')
	{
		i--;
		j++;
	}
	str = ft_substr(buf, i + 1, j);
	ft_putstr_fd(str, 1);
	free(str);
	write(1, ")\033[31m#>\033[00m ", 15);
	g_env.is_join = 0;
	// dprintf(2, "is join signal{%d}\n", g_env.is_join);
}

void		ft_sig_quit(int sig_id)
{
	(void)sig_id;
	ft_putstr_fd("\b \b\b \b", 2);
}
