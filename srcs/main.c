/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/05 15:40:59 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_env *env)
{
	int		ret;

	while ((ret = get_next_line(0, &env->arg)) > 0)
	{
		ret = -1;
		while (++ret == 0 || (env->arg = ft_strchr(env->arg, ';')))
		{
			ret != 0 ? env->arg++ : 0;
			while (*env->arg < 33 && *env->arg)
				env->arg++;
			if (!*env->arg || (*env->arg == ';' && !(*env->arg + 1)))
				return ;
			is_pipe_here(env) ? is_command(env->arg, env) : 0;
		}
		free(env->arg);
		break ;
	}
}

int		main(int ac, char **av, char **envi)
{
	t_env	*env;

	(void)ac;
	(void)av;
	if ((!(env = (t_env*)malloc(sizeof(t_env)))))
		return (0);
	env->exit = 0;
	env->my_env = envi;
	env->var = ft_lstvar(env);
	while (1)
	{
		write(1, "\033[31m<#\033[34m(", 14);
		ft_get_dir(env);
		write(1, env->dir, ft_strlen(env->dir));
		free(env->dir);
		write(1, ")\033[31m#>\033[00m ", 15);
		loop_shell(env);
		if (env->exit != 0)
			break ;
	}
}
