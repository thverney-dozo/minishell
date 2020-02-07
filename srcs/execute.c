/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:20:16 by thverney          #+#    #+#             */
/*   Updated: 2020/02/07 00:25:12 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_executable(t_env *env, int indic)
{
	struct dirent		*dirent;
	DIR			*dir;
	int i;
	int ret;
	int errno;

	errno = 0;
	if (indic)
		return (0);
	else
	{
		if (!(dirent = (struct dirent*)malloc(sizeof(struct dirent))))
			return (0);
		i = 0;
		while (env->path[i])
		{
			if (!(dir = opendir(env->path[i])))
				return (-1);
			while ((dirent = readdir(dir)) != NULL)
			{
				if (!(ft_strcmp(dirent->d_name, env->flags[0])))
				{

					printf("|%s|\n", dirent->d_name);
					printf("|%s|\n", env->path[i]);
					printf("|%s|\n", ft_strjoin(ft_strjoin(env->path[i], "/"), dirent->d_name));
					printf("|%s|\n", env->flags[0]);
					printf("|%s|\n", env->flags[1]);
					ret = execve(ft_strjoin(ft_strjoin(env->path[i], "/"), dirent->d_name), env->flags, env->my_env);
					if (errno)
						printf("|%s|\n", strerror(errno));
					printf("|%d|\n", ret);
					return (1);
				}
			}
			closedir(dir);
			i++;
		}
		return (0);
	}	

}
