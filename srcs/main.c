/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/01/29 11:24:24 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	loop_shell(t_env *env)
{
	int		ret;
	char	*line;

	(void)env;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		is_command(line);
		if (line[0] == '\0')
			return ;
		if (line[ft_strlen(line)] == '\0')
			break ;
	}
}

int		main(void)
{

	t_env *env;
	if ((!(env = (t_env*)malloc(sizeof(t_env)))))
		return (0);
	env->exit = 0;
	while (1)
	{
		write(1, "\033[31m<#minishell#>\033[0m ", 24);
		loop_shell(env);
		if (env->exit != 0)
			break ;
	}
}
