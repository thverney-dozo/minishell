/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:01:38 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/26 04:46:42 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_screen(t_env *env)
{
	const char *clear_screen;

	(void)env;
	clear_screen = "\033c";
	write(1, clear_screen, 3);
}
