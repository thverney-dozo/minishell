/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:54:21 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/25 04:40:04 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env g_env;

int		syntax_error(t_env *env)
{
	env->i = 0;
	if (!(env->copy_free[env->i]) || !(env->copy_free))
		return (1);
	env->ret = 0;
	while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
		env->i++;
	if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
		return (ft_error_syntax(env));
	while (env->copy_free[env->i])
	{
		if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
		{
			env->copy_free[env->i] ? env->i++ : 0;
			while (env->copy_free[env->i] && env->copy_free[env->i] < 33)
				env->i++;
			if (env->copy_free[env->i] == '|' || env->copy_free[env->i] == ';')
				return (ft_error_syntax(env));
		}
		env->i++;
	}
	return (0);
}

void	loop_shell(t_env *env)
{
	if ((env->ret_gnl = get_next_line(0, &env->copy_free)) > 0
	&& env->ret_gnl != 2)
	{
		env->is_join = g_env.is_join;
		if (g_env.is_join == 0)
		{
			if (env->copy_free)
			{
				free(env->copy_free);
				env->copy_free = NULL;
			}
			env->is_join = 1;
			return ;
		}
		if (env->join && env->is_join)
			env->copy_free = ft_strjoin(env->join, env->copy_free);
		env->is_join = 1;
		if (syntax_error(env))
			return ;
		if ((env->args = split_commands(env)) == NULL)
			return ;
		ft_clear(&env->copy_free);
		env->i = 0;
		while (env->args[env->i])
		{
			if (env->args[env->i])
				is_pipe_here(env);
			free(env->args[env->i]);
			env->args[env->i] = NULL;
			env->i++;
		}
		free(env->args);
		env->args = NULL;
	}
	if (env->ret_gnl == 2 && env->copy_free)
	{
		env->join = env->join ? ft_strdup(env->copy_free) : NULL;
	}
	else if (env->ret_gnl == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	prompt_display(t_env *env)
{
	if (env->ret_gnl != 2)
	{
		write(1, "\033[31m<#\033[34m(", 14);
		ft_get_dir(env);
		ft_putstr_fd(env->dir, 1);
		free(env->dir);
		write(1, ")\033[31m#>\033[00m ", 15);
	}

	loop_shell(env);
}

void	get_signal(void)
{
	signal(SIGINT, ft_sig_kill);
	signal(SIGQUIT, ft_sig_quit);
}

int		main(int ac, char **av, char **envi)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = &g_env;
	if ((!(env = (t_env*)malloc(sizeof(t_env)))))
		return (0);
	env->exit = 0;
	env->my_env = envi;
	env->var = ft_lstvar(env);
	env->fd_red = 1;
	env->ret_gnl = 0;
	env->join = NULL;
	g_env.is_join = 1;
	env->copy_free = NULL;
	get_signal();
	while (1)
	{
		prompt_display(env);
		if (env->exit != 0)
			break ;
	}
}
