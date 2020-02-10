/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:20:16 by thverney          #+#    #+#             */
/*   Updated: 2020/02/10 20:10:42 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_executable(t_env *env, int indic)
{
	struct dirent		*dirent;
	DIR			*dir;
	int i;
	int errno;

	errno = 0;
	if (indic)
		return (0);
	else
	{
		env->flags = split_wh_sp(env->av_pipe[env->x]);
		if (env->flags[0][0] == '.' && env->flags[0][1] == '/')
		{
			execve(*env->flags + 2, env->flags, env->my_env);
			if (errno)
				write(1, strerror(errno), ft_strlen(strerror(errno)));
		}
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
						execve(ft_strjoin(ft_strjoin(env->path[i], "/"), dirent->d_name), env->flags, env->my_env);
						if (errno)
							write(1, strerror(errno), ft_strlen(strerror(errno)));
				// dprintf(2, "SEGFAULT\n");
						return (1);
					}
				}
				closedir(dir);
				i++;
			}
		}
		return (0);
	}
}
