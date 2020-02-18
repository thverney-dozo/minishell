/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:39:39 by thverney          #+#    #+#             */
/*   Updated: 2020/02/18 15:42:01 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		next_space(char *str, int i)
{
	while (str[i] && str[i] > 32)
		i++;
	return (i);
}

int		next_none_space(char *str, int i)
{
	while (str[i] && str[i] < 33)
		i++;
	return (i);
}

int		ft_error_syntax(t_env *env)
{
	write(2, "minishell : syntax error near unexpected token '", 49);
	ft_putchar_fd(env->copy_free[env->i] , 2);
	write(2, "'\n", 3);
	free(env->copy_free);
	env->copy_free = NULL;
	return (1);
}
