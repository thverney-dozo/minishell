/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/06 14:24:50 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_env *env)
{
	int		i;

	while ((i = get_next_line(0, &env->copy_free)) > 0)
	{
		env->args = ft_split(env->copy_free, ';');
		free(env->copy_free);
		env->copy_free = NULL;
		env->i = 0;
		while (env->args[env->i])
		{
			env->j = 0;
			while (env->args[env->i][env->j] && env->args[env->i][env->j] < 33)
				env->j++;
			if (env->args[env->i][env->j] && env->args[env->i][env->j]  != ';'
			&& env->args[env->i][env->j] != '|')
				is_pipe_here(env);
			free(env->args[env->i]);
			env->args[env->i] = NULL;
			env->i++;
		}
		break ;
	}
	free(env->args);
	env->args = NULL;
}

void	prompt_display(t_env *env)
{
	write(1, "\033[31m<#\033[34m(", 14);
	ft_get_dir(env);
	write(1, env->dir, ft_strlen(env->dir));
	free(env->dir);
	write(1, ")\033[31m#>\033[00m ", 15);
	loop_shell(env);
	if (env->exit != 0)
		return ;
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
		prompt_display(env);
}
