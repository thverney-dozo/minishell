NAME    =       Minishell

# Sources

SRC_FILE   =   main.c 			\
			ft_echo.c			\
			ft_not_found.c		\
			pwd.c				\
			cd.c				\
			env.c				\
			lst.c				\
			unset.c				\
			redir.c			 	\
			use_env_var.c		\
			clear_screen.c		\
			signals.c			\
			execute.c			\
			iscmd.c 			\
			iscmd2.c			\
			split_commands.c	\
			split_commands2.c	\
			split_commands3.c	\
			split_pipes.c		\
			split_pipes2.c		\
			split_pipes3.c		\
			export.c			\
			export2.c		 	\
			export3.c			\
			utils.c				\
			utils2.c			\
			utils3.c			\
			utils4.c			\

INCS_NAME   =   minishell.h

LIB_NAME    =   libft.a

# Directories

SRCS_DIR    =   ./srcs/
OBJS_DIR    =   ./objs/
INCS_DIR    =   ./includes/
LIB_DIR     =   ./libft/

# Files

SRCS        =   $(addprefix $(SRCS_DIR), $(SRC_FILE))
OBJS        =   $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
INCS        =   $(addprefix $(INCS_DIR), $(INCS_NAME))
LIB         =   $(addprefix $(LIB_DIR), $(LIB_NAME))

# Compilation

CC          =   gcc
CFLAGS      =   -Wall -Wextra -Werror -g3 -I $(INCS_DIR)
CFLAGS_DEBUG=   -Wall -Wextra -Werror -g3 -fsanitize=address -I $(INCS_DIR)

LIBH        =   -I $(LIB_DIR)includes/

all: $(NAME)

$(LIB):
	@make -j -sC $(LIB_DIR)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[32;01m[Minishell OK]\033[00m"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCS)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(LIBH) -o $@ -c $<

librm:
	@make -sC libft fclean
	@echo "\033[32;01m[Libft fclean OK]\033[00m"

clean:
	@rm -rf $(OBJS_DIR)
	@make -C libft clean

fclean: librm clean
	@rm -f ${NAME}
	@echo "\033[32;01m[Minishell fclean OK]\033[00m"

debug: $(LIB) $(OBJS)
	@$(CC) $(CFLAGS_DEBUG) $(LIB) $(OBJS) -o $(NAME)
	@echo "\033[32;01m[Minishell DEBUG]\033[00m"

re: fclean all

.PHONY: all librm clean fclean re
