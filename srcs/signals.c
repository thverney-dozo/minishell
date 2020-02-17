/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:41:17 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/17 18:11:00 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_sig_kill(int sig_id)
{
	(void)sig_id;
	ft_putstr_fd("\n", 1);
}

void		ft_sig_quit(int sig_id)
{
	(void)sig_id;
}
