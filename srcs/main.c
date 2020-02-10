/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:43:30 by thverney          #+#    #+#             */
/*   Updated: 2020/02/10 11:59:56 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_error(t_env *env)
{
	env->i = 0;
	while (env->copy_free[env->i] < 33 && env->copy_free[env->i])
		env->i++;
	if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
	{
		write(1, "minishell : syntax error near unexpected token '", 49);
		ft_putchar_fd(env->copy_free[env->i] , 1);
		write(1, "'\n", 3);
		free(env->copy_free);
		env->copy_free = NULL;
		return (1);
	}
	return (0);
}

void	loop_shell(t_env *env)
{
	if ((env->i = get_next_line(0, &env->copy_free)) > 0)
	{
		if (syntax_error(env))
			return ;
		if ((env->args = split_commands(env)) == NULL)
			return ;
		free(env->copy_free);
		env->copy_free = NULL;
		env->i = 0;
		while (env->args[env->i])
		{
			env->j = 0;
			env->flags = split_wh_sp(env->args[env->i]);
			while (env->args[env->i][env->j] && env->args[env->i][env->j] < 33)
				env->j++;
			if (env->args[env->i][env->j] && env->args[env->i][env->j] != '|')
				is_pipe_here(env);
			free(env->flags);
			env->flags = NULL;
			free(env->args[env->i]);
			env->args[env->i] = NULL;
			env->i++;
		}
		free(env->args);
		env->args = NULL;
	}
}

void	prompt_display(t_env *env)
{
	write(1, "\033[31m<#\033[34m(", 14);
	ft_get_dir(env);
	write(1, env->dir, ft_strlen(env->dir));
	free(env->dir);
	write(1, ")\033[31m#>\033[00m ", 15);
	loop_shell(env);
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
		prompt_display(env);
		if (env->exit != 0)
			break ;
	}
}
