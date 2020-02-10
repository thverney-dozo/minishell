/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/02/10 17:56:46 by thverney         ###   ########.fr       */
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
# include <dirent.h>

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct		s_cmd
{
	int				index;
	int				error;
	char			*cpy;
	int				words;
	int				wichquote;
	int				backslash;
}					t_cmd;

typedef struct		s_env
{
	int			max;
	int			count;
	int			fd[2];
	int			old_fd;
	int			input_pipe;
	int			exit;
	char		*buf;
	char		*arg;
	char		**my_env;
	char		*dir;
	char		**args;
	char		**flags;
	int			i;
	int			j;
	int			x;
	int			y;
	char		**copy_args;
	char		*copy_free;
	char		**av_pipe;
	char		**copy_pipe;
	char		**path;	
	t_var		*var;
	t_var		*first;
	t_var		*save;
	
}				t_env;

void			loop_shell(t_env *env);
void			is_command(char *cmd, t_env *env);
void			ft_echo(t_env *env);
void			ft_echo_n(int i, int tmp, t_env *env);
void			ft_echo_two(t_env *env);
void			ft_not_found(char *cmd);
void			ft_pwd(void);
void			ft_cd(t_env *env);
void			ft_env(t_env *env);
void			is_pipe_here(t_env *env);
void			ft_pipe_is_cmd(t_env *env, int old_fd);
void			verify_cmd_pipe(char *cmd, int indic, t_env *env);
void			ft_get_dir(t_env *env);
void			ft_export(char *str, t_env *env);
t_var			*ft_lstvar(t_env *env);
void			ft_save(t_env *env, t_var *var);
void			ft_lstaddvar2(t_var *new, t_env *env);
void			ft_lstaddvar(t_var **alst, t_var *new);
t_var			*ft_lstnewvar(char *var, int i, t_env *env);
int				ft_find_char(char *str, char c);
int				ft_verif_var(char *name, t_env *env, char *value);
void			ft_clear(void);
void			ft_unset(char *str, t_env *env);
void			ft_unset_var(char *str, t_env *env);
char			*ft_get_home(t_env *env);
int				is_executable(t_env *env, int indic);
char			**split_commands(t_env *env);
int				is_multi_line_quote(t_cmd *cmd, int i);
void			is_multi_line_quote_two(t_cmd *cmd, int i);
char			*get_semi_coma(t_cmd *cmd, char *str, char c);
int				how_many_backslash(char *str, int i, t_cmd *cmd);
char			*get_semi_coma(t_cmd *cmd, char *str, char c);
void			is_word(t_cmd *cmd, int i);
char			**split_pipes(t_env *env);
#endif
