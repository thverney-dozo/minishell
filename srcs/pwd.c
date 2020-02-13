/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:22:22 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/13 17:56:01 by aeoithd          ###   ########.fr       */
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
	env->var = env->first;
	getcwd(buf, PATH_MAX);
	if (!ft_strcmp(buf, tmp))
	{
		env->dir = ft_strdup("~");
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

void	ft_pwd(void)
{
	char	buf[PATH_MAX + 1];
	int		errno;

	if (!getcwd(buf, PATH_MAX))
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(getcwd(buf, PATH_MAX), 1);
}
