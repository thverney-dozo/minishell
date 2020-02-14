/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:01:38 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/14 13:36:02 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_screen(t_env *env)
{
	const char *clear_screen;

	clear_screen = "\033c";
	write(env->fd_red, clear_screen, 3);
}
