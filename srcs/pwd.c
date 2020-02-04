/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:22:22 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/03 22:50:02 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_dir(t_env *env)
{
	int		i;
	int		j;
	char	buf[PATH_MAX + 1];

	i = 0;
	j = 0;
	getcwd(buf, PATH_MAX);
	while (buf[i] > 32)
		i++;
	while (buf[i] != '/')
	{
		i--;
		j++;
	}
	env->dir = ft_substr(buf, i, j);
	
}

void	ft_pwd(char *str, int i)
{
	char	buf[PATH_MAX + 1];

	while (str[i] != '\0' && str[i] < 33)
		i++;
	if (str[i] == '\0' || str[i] == '|' || str[i] == ';')
		ft_putendl_fd(getcwd(buf, PATH_MAX), 1);
	else
		write(1, "pwd: too many arguments", 24);
}
