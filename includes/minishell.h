/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/02/03 22:51:59 by thverney         ###   ########.fr       */
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
# include <limits.h>

typedef struct	s_env
{
	int			exit;
	char		*buf;
	char		*pos_prev;
	char		*pos_next;
	char		**my_env;
	int			pipe_here;
	char		*dir;
}				t_env;

void			loop_shell(t_env *env);
void        	is_command(char *cmd, t_env *env);
void			ft_echo(char *cmd);
void			ft_not_found(char *cmd);
void			ft_pwd(char *str, int i);
void			ft_cd(char *path);
void			ft_env(t_env *env);
void			is_pipe_here(t_env *env);
void			verify_cmd_pipe(char *cmd, int indic, t_env *env);
void			ft_cd_two(char *tmp, char *path, int i);
void			ft_get_dir(t_env *env);

#endif
