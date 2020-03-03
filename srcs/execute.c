/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:20:16 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 02:34:21 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exec_three(t_env *env, struct dirent	*dirent)
{
	t_var	*tmp;

	if (!(dirent = (struct dirent*)malloc(sizeof(struct dirent))))
		return (1);
	tmp = env->first;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH\0"))
		{
			env->path = ft_split(tmp->value, ':');
			return (0);
		}
		tmp = tmp->next;
	}
	env->path = NULL;
	return (1);
}

int		is_exec_two(t_env *env, int i, struct dirent *dirent)
{
	DIR				*dir;

	if (is_exec_three(env, dirent))
		return (0);
	while (env->path[++i])
	{
		if (!(dir = opendir(env->path[i])))
			return (-1);
		while ((dirent = readdir(dir)) != NULL)
		{
			if (!(ft_strcmp(dirent->d_name, env->flags[env->x][0])))
			{
				execve(ft_strjoin(ft_strjoin(env->path[i], "/"),
				dirent->d_name), env->flags[env->x], env->my_env);
				if (errno)
					write(2, strerror(errno), ft_strlen(strerror(errno)));
				return (1);
			}
		}
		closedir(dir);
	}
	free(dirent);
	dirent = NULL;
	return (0);
}

int		is_executable(t_env *env, int indic)
{
	struct dirent	*dirent;

	dirent = NULL;
	if (indic)
		return (0);
	else
	{
		env->flags[env->x] = split_wh_sp(env->av_pipe[env->x]);
		if (env->flags[env->x][0][0] == '.' || env->flags[env->x][0][0] == '/')
		{
			execve(*env->flags[env->x], env->flags[env->x], env->my_env);
			if (errno)
			{
				ft_putendl_fd(strerror(errno), 2);
				return (1);
			}
		}
		return (is_exec_two(env, -1, dirent));
	}
}
