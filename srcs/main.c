/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/04 01:33:48 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_env *env)
{
	int		ret;
	char	*line;
	
	while ((ret = get_next_line(0, &line)) > 0)
	{
		
		while (*line < 33 && *line != '\0')
			line++;
		if (line[0] == '\0' || (line[0] == ';' && line[1] == '\0'))
			return ;
		env->pos_prev = line;
		is_pipe_here(env);
		env->pipe_here == 0 ? is_command(env->pos_prev, env) : 0;
		env->pos_next = env->pos_prev;
		while ((env->pos_prev = ft_strchr(env->pos_next, ';')))
		{
			env->pos_prev++;
			while (*env->pos_prev < 33 && *env->pos_prev != '\0')
				env->pos_prev++;
			if (env->pos_prev[0] == '\0')
				return ;
			env->pos_next = ft_strchr(env->pos_prev, ';');
			is_pipe_here(env);
			env->pipe_here == 0 ? is_command(env->pos_prev, env) : 0;
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
