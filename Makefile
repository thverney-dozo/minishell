CFLAGS = -Wall -Werror -Wextra
NAME = Minishell

SRC_FILE = main.c \

GNL_FILE = get_next_line.c get_next_line_utils.c

LIB_PATH = libft/
LIB_FILE = ft_split.c \
ft_substr.c \
ft_calloc.c \
ft_bzero.c \
ft_strjoin.c \
ft_atoi.c \
ft_putstr_fd.c \
ft_putchar_fd.c \
ft_strchr.c \
ft_sdupfr.c \
ft_isdigit.c \
ft_strlen.c \
ft_sjoin_free.c \
ft_strncmp.c	\

GNL_PATH = gnl/
INC= minishell.h
SRC = ${SRC_FILE} ${addprefix ${GNL_PATH}, $(GNL_FILE)} ${addprefix ${LIB_PATH}, $(LIB_FILE)}
OBJS = ${SRC:%.c=%.o}

all: ${NAME}

$(NAME): ${OBJS} ${INC}
	@gcc ${CFLAGS} ${OBJS} -o ${NAME}

%.o : %.c
	@echo Compiling $<
	@gcc $(CFLAGS) -c -I include/ $< -o $@

clean:
	@rm -f ${OBJS} ${BONUS}

fclean: clean
	@rm ${NAME}

bonus :

re: clean all