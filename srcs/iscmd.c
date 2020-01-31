/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:08:15 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/31 16:06:09 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        is_command(char *cmd, t_env *env)
{
    if (!ft_strncmp(cmd, "exit", 5))
		exit (1);
    else if (!(ft_strncmp(cmd, "echo ", 5)) || !ft_strncmp(cmd, "echo", 5))
        ft_echo(cmd);
    else if (!(ft_strncmp(cmd, "pwd", 3)))
        ft_pwd();
    else if (!(ft_strncmp(cmd, "cd", 2)))
        ft_cd(cmd + 3);
    else if (!(ft_strncmp(cmd, "env", 3) || !(ft_strncmp(cmd, "env ", 4))))
        ft_env(env);
    else if (cmd[0] != '\0')
        ft_not_found(cmd);
}
