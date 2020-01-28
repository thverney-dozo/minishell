/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/28 16:59:24 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        is_command(char *cmd)
{
    if (!ft_strncmp(cmd, "exit", 5))
		exit (1);
    if (!(ft_strncmp(cmd, "echo", 4)))
        ft_echo(cmd);
    else
        ft_not_found(cmd);
}
