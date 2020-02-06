/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:22:22 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/06 14:28:53 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_dir(t_env *env)
{
	int		i;
	int		j;
	char	buf[PATH_MAX + 1];
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_get_home(env);
	getcwd(buf, PATH_MAX);
	if (!ft_strcmp(buf, tmp))
	{
		env->dir = ft_strdup("~");
		env->var = env->first;
		return ;
	}
	while (buf[i] >= 32)
		i++;
	while (buf[i] != '/')
	{
		i--;
		j++;
	}
	env->dir = ft_substr(buf, i + 1, j);
}

void	ft_pwd(char *str, int i)
{
	char	buf[PATH_MAX + 1];

	while (str[i] && str[i] < 33)
		i++;
	if (!str[i] || str[i] == '|' || str[i] == ';')
		ft_putendl_fd(getcwd(buf, PATH_MAX), 1);
	else
		write(1, "pwd: too many arguments\n", 25);
}
