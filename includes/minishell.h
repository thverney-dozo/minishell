/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:49:54 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 08:11:07 by thverney         ###   ########.fr       */
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
	int				fd_red;
	int				ret;
	int				count_char_redir;
	int				nb_redir;
	int				t;
	int				ret_gnl;
	int				is_join;
	int				count_redir;
	int				count;
	int				fd[2];
	int				old_fd;
	int				input_pipe;
	int				exit;
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	char			*isred;
	char			*line;
	char			*join;
	char			*dir;
	char			*copy_free;
	char			**redir;
	char			**my_env;
	char			**args;
	char			**av_pipe;
	char			**pipe[2];
	char			**path;
	char			***flags;
	t_var			*var;
	t_var			*first;
	t_var			*save;
}					t_env;

extern				t_env g_env;
/*
**	Main and redirections
*/
int					loop_shell(t_env *env);
void				is_command(char *cmd, t_env *env);
void				is_pipe_here(t_env *env);
void				is_pipe_here_two(t_env *env);
void				ft_pipe_is_cmd(t_env *env, int old_fd);
void				verify_cmd_pipe(char *cmd, int indic, t_env *env);
char				**split_commands(t_env *env);
int					is_multi_line_quote(t_cmd *cmd, int i);
void				is_multi_line_quote_two(t_cmd *cmd, int i);
void				is_multi_line_quote_pipe(t_cmd *cmd, int i);
void				is_multi_line_quote_two_pipe(t_cmd *cmd, int i);
char				**split_pipes(t_env *env);
int					stock_file(char *str, int tmp, t_env *env);
void				ft_redir(t_env *env);
void				set_fd_redirection(t_env *env);
void				restore_fd_redirection(t_env *env);
int					count_dollar(t_env *env, char *str);
int					replace_word(t_env *env, char *line, char *str, char *cpy);
void				child_ps(t_env *env, int old_fd);
void				parent_ps(t_env *env, int old_fd, int pid);
char				**split_parse(t_env *env, t_cmd *cmd, int i);
int					count_chars(t_cmd *cmd, char *line);
void				is_multi_line_quote_pipe(t_cmd *cmd, int i);
void				count_chars_pipes(char *line, t_env *env, int i);
int					split_pipe_dbquote(int i, t_env *env);
int					split_pipe_line_two(int i, t_env *env);
/*
**	Utils
*/
int					nbslash(char *str, int i);
int					next_space(char *str, int i);
int					next_none_space(char *str, int i);
int					count_redir_file(char *str, int i);
int					ft_error_syntax(t_env *env);
int					is_builtin_no_pipe(char *cmd, t_env *env);
int					syntax_error(t_env *env);
void				fill_triple_string(t_env *env, int j, char slash,
char line);
int					is_forbidden_letter(char c);
int					malloc_triple_tab(t_env *env, t_cmd *cmd);
int					malloc_tab(t_env *env);
void				how_many_redir(t_env *env);
int					blank_line(t_env *env);
void				join_gnl_loop(t_env *env);

/*
**	Free
*/
int					free_syntax_error(t_env *env);
void				free_pipe(t_env *env, int i, int pipe);
void				free_args(t_env *env);
void				free_flags(t_env *env);
void				free_pipe_two(t_env *env);
void				free_pipe_fork(t_env *env, int i, int pipe);
void				free_cmd(t_cmd *cmd);
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
void				ft_export_error(char *str);

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
void				ft_not_found(char *cmd, t_env *env);

/*
**	Clear screen
*/
void				ft_clear_screen(t_env *env);

/*
**	Redirections
*/
void				ft_redir(t_env *env);

/*
**	Signals
*/
void				ft_sig_kill(int sig_id);
void				ft_sig_quit(int sig_id);

int					is_executable(t_env *env, int indic);
void				is_word(t_cmd *cmd, int i);
#endif
