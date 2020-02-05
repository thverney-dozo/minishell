/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/02/05 14:11:56 by anloubie         ###   ########.fr       */
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

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct		s_env
{
	int			exit;
	char		*buf;
	char		*arg;
	char		**my_env;
	char		*dir;
	t_var		*var;
	t_var		*first;
	t_var		*save;
	
}				t_env;

void			loop_shell(t_env *env);
void			is_command(char *cmd, t_env *env);
void			ft_echo(char *cmd);
void			ft_not_found(char *cmd);
void			ft_pwd(char *str, int i);
void			ft_cd(char *path, t_env *env);
void			ft_env(t_env *env);
int				is_pipe_here(t_env *env);
void			verify_cmd_pipe(char *cmd, int indic, t_env *env);
void			ft_cd_two(char *tmp, char *path, int i);
void			ft_get_dir(t_env *env);
void			ft_export(char *str, t_env *env);
t_var			*ft_lstvar(t_env *env);
void			ft_save(t_env *env, t_var *var);
void			ft_lstaddvar2(t_var *new, t_env *env);
void			ft_lstaddvar(t_var **alst, t_var *new);
t_var			*ft_lstnewvar(char *var, int i);
int				ft_find_char(char *str, char c);
int				ft_verif_var(char *name, t_env *env, char *value);
void			ft_clear(void);
void			ft_unset(char *str, t_env *env);
void			ft_unset_var(char *str, t_env *env);

#endif
