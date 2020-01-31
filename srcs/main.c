/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/01/31 16:05:37 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_shell(t_env *env)
{
	int		ret;
	char	*line;
	
	(void)env;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		while (*line < 33 && *line != '\0')
			line++;
		if (line[0] == '\0' || (line[0] == ';' && line[1] == '\0'))
			return ;
		env->pos_prev = line;
		is_command(env->pos_prev, env);
		env->pos_next = env->pos_prev;
		while ((env->pos_prev = ft_strchr(env->pos_next, ';')))
		{
			env->pos_prev++;
			while (*env->pos_prev < 33 && *env->pos_prev != '\0')
				env->pos_prev++;
			if (env->pos_prev[0] == '\0')
				return ;
			env->pos_next = ft_strchr(env->pos_prev, ';');
			is_command(env->pos_prev, env);
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
		write(1, "\033[31m<#minishell#>\033[0m ", 24);
		loop_shell(env);
		if (env->exit != 0)
			break ;
	}
}
