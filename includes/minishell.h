/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/02/17 00:58:21 by thverney         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>

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
	char			*isred;
	int				count_redir;
	char			**redir;
	int				count;
	int				fd[2];
	int				old_fd;
	int				input_pipe;
	int				exit;
	char			*buf;
	char			*arg;
	char			**my_env;
	char			*dir;
	char			**args;
	char			**flags;
	int				i;
	int				j;
	int				x;
	int				y;
	char			**copy_args;
	char			*copy_free;
	char			**av_pipe;
	char			**cpy_pipe;
	char			**path;	
	t_var			*var;
	t_var			*first;
	t_var			*save;
	int				fd_red;
}					t_env;

/*
**	Main and redirections
*/
void				loop_shell(t_env *env);
void				is_command(char *cmd, t_env *env);
void				is_pipe_here(t_env *env);
void				ft_pipe_is_cmd(t_env *env, int old_fd);
void				verify_cmd_pipe(char *cmd, int indic, t_env *env);
char				**split_commands(t_env *env);
int					is_multi_line_quote(t_cmd *cmd, int i);
void				is_multi_line_quote_two(t_cmd *cmd, int i);
char				*get_semi_coma(t_cmd *cmd, char *str, char c);
char				*get_semi_coma(t_cmd *cmd, char *str, char c);
char				**split_pipes(t_env *env);
int					stock_redir_file(char *str, int tmp, t_env *env, t_cmd *cmd);
void				ft_redir(t_env *env);
void				set_fd_redirection(t_env *env);
void				restore_fd_redirection(t_env *env);

/*
**	Utils
*/
int					how_many_backslash(char *str, int i, t_cmd *cmd);
int					next_space(char *str, int i);
int					next_none_space(char *str, int i);
int					count_redir_file(char *str, int i, t_cmd *cmd);

/*
**	Echo
*/
void				ft_echo(t_env *env);
void				ft_echo_n(int i, int tmp, t_env *env);
void				ft_echo_two(t_env *env);

/*
**	Cd
*/
void				ft_cd(t_env *env);

/*
**	Pwd
*/
void				ft_pwd(void);
void				ft_get_dir(t_env *env);

/*
**	Env
*/
void				ft_env(t_env *env);
void				ft_save(t_env *env, t_var *var);
void				ft_lstaddvar2(t_var *new, t_env *env);
void				ft_lstaddvar(t_var **alst, t_var *new);
t_var				*ft_lstnewvar(char *var, int i, t_env *env);
int					ft_find_char(char *str, char c);
int					ft_verif_var(char *name, t_env *env, char *value);
t_var				*ft_lstvar(t_env *env);

/*
**	Export
*/
void				ft_export(t_env *env);
int					ft_count_env(t_env *env);
int					ft_buflen(char **buf);
void				env_malloc(t_env *env);

/*
**	Unset
*/
void				ft_unset(t_env *env);
void				ft_unset_var(char *str, t_env *env);

/*
**	$$
*/
char				*ft_get_home(t_env *env);
void				ft_use_env_var(t_env *env);

/*
**	Not found
*/
void				ft_not_found(char *cmd);

/*
**	Clear screen
*/
void				ft_clear_screen(t_env *env);

/*
**	Redirections
*/
void				ft_redir(t_env *env);

int					is_executable(t_env *env, int indic);
void				is_word(t_cmd *cmd, int i);
#endif
