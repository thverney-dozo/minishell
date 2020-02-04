/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/04 04:54:01 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_env *env)
{
	int		ret;
	
	while ((ret = get_next_line(0, &env->pos_prev)) > 0)
	{
		ret = -1;
		while (++ret == 0 || (env->pos_prev = ft_strchr(env->pos_prev, ';')))
		{
			ret != 0 ? env->pos_prev++ : 0;
			while (*env->pos_prev < 33 && *env->pos_prev != '\0')
				env->pos_prev++;
			if (*env->pos_prev == '\0' || (*env->pos_prev == ';' && *env->pos_prev + 1 == '\0'))
				return ;
			is_pipe_here(env) ? is_command(env->pos_prev, env) : 0;
		}
		break ;
	}
}

int		main(int ac, char **av, char **envi)
{
	t_env *env;

	(void)ac;
	(void)av;
	if ((!(env = (t_env*)malloc(sizeof(t_env)))))
		return (0);
	env->exit = 0;
	env->my_env = envi;
	while (1)
	{
		write(1, "\033[31m<#\033[34m(", 14);
		ft_get_dir(env);
		write(1, env->dir, 10);
		write(1, ")\033[31m#>\033[00m ", 15);
		loop_shell(env);
		if (env->exit != 0)
			break ;
	}
}
