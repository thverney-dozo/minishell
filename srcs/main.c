/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:54:21 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/14 14:12:42 by anloubie         ###   ########.fr       */
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
		write(2, "minishell : syntax error near unexpected token '", 49);
		ft_putchar_fd(env->copy_free[env->i] , 2);
		write(2, "'\n", 3);
		free(env->copy_free);
		env->copy_free = NULL;
		return (1);
	}
	else if (!(env->copy_free[env->i]))
		return (1);
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
		//dprintf(2, "#######split commands fonctionne#######\n");
		// int i = 0;
		// while (env->args[i])
		// {
			//dprintf(2, "command[%d] = {%s} taille {%zu}\n", i, env->args[i], ft_strlen(env->args[i]));
			// i++;
		// }
		//dprintf(2, "#####################################\n\n");
		//dprintf(2, "Il y a %d commandes\n", i);
		ft_clear(&env->copy_free);
		env->i = 0;
		while (env->args[env->i])
		{
			env->j = 0;
			if (env->args[env->i])
				is_pipe_here(env);
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
	ft_putstr_fd(env->dir, 1);
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
	env->fd_red = 1;
	while (1)
	{
		prompt_display(env);
		if (env->exit != 0)
			break ;
	}
}
