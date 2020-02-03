/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/02/03 14:17:25 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct	s_env
{
	int			exit;
	char		*buf;
	char		*pos_prev;
	char		*pos_next;
	char		**my_env;
	int			pipe_here;
}				t_env;

void			loop_shell(t_env *env);
void        	is_command(char *cmd, t_env *env);
void			ft_echo(char *cmd);
void			ft_not_found(char *cmd);
void			ft_pwd(void);
void			ft_cd(char *path);
void			ft_env(t_env *env);

#endif
