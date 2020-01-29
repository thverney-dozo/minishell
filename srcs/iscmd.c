/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/29 13:59:56 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        is_command(char *cmd)
{
    if (!ft_strncmp(cmd, "exit", 5))
		exit (1);
    else if (!(ft_strncmp(cmd, "echo ", 5)) || !ft_strncmp(cmd, "echo", 5))
        ft_echo(cmd);
    else if (!(ft_strncmp(cmd, "pwd", 3)))
        ft_pwd();
    else if (!(ft_strncmp(cmd, "cd", 2)))
        ft_cd(cmd + 3);
    else if (cmd[0] != '\0')
        ft_not_found(cmd);
}
