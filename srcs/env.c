/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:55:10 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/31 16:06:52 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->my_env[i])
	{
		write(1, env->my_env[i], ft_strlen(env->my_env[i]));
		write(1, "\n", 1);
		i++;
	}
}
