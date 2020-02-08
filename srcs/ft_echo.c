/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/08 22:26:23 by thverney         ###   ########.fr       */
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

void		ft_echo(char *cmd, t_env *env)
{
	char	*new;
	int		i;
	int		tmp;

	if (!ft_strncmp(env->flags[1], "-n\n", 3))
	{
		ft_echo_n(cmd, 0);
		return ;
	}
	if (env->av_pipe[env->x + 1])
	{
		i = 0;
		while (env->av_pipe[env->x][i] < 33 && env->av_pipe[env->x][i])
			i++;
		while (env->av_pipe[env->x][i] > 32 && env->av_pipe[env->x][i])
			i++;
		while (env->av_pipe[env->x][i] < 33 && env->av_pipe[env->x][i])
			i++;
		tmp = i;
		while (env->av_pipe[env->x][tmp])
			tmp++;
		tmp--;
		while (env->av_pipe[env->x][tmp - 1] < 33 && env->av_pipe[env->x][tmp - 1])
			tmp--;
		new = ft_substr(env->av_pipe[env->x], i, tmp - i);
		if (new[0])
			write(1, new, ft_strlen(new));
	}
	write(1, "\n", 1);
}
