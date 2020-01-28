# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thverney <thverney@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 19:13:28 by thverney          #+#    #+#              #
#    Updated: 2020/01/16 01:17:20 by thverney         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = libft.h

FILES = 		ft_atoi.c \
                ft_bzero.c \
                ft_isalnum.c \
                ft_isalpha.c \
                ft_isascii.c \
                ft_isdigit.c \
                ft_isprint.c \
                ft_memccpy.c \
                ft_memcpy.c \
                ft_memset.c \
                ft_strdup.c \
                ft_strlen.c \
                ft_strncmp.c \
                ft_tolower.c \
                ft_toupper.c \
                ft_memmove.c \
                ft_strnstr.c \
                ft_calloc.c \
                ft_memchr.c \
                ft_memcmp.c \
                ft_memcpy.c \
                ft_strchr.c \
                ft_strrchr.c \
                ft_strdup.c \
                ft_strjoin.c \
                ft_substr.c \
                ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
                ft_putnbr_fd.c \
                ft_split.c \
                ft_strtrim.c \
                ft_strlcat.c \
                ft_strlcpy.c \
                ft_strmapi.c \
				ft_itoa.c \
                ft_sdupfr.c \
				ft_sjoin_free.c \

OBJECTS = $(FILES:.c=.o)

FLAGS = -Wall \
		-Werror \
		-Wextra

all : $(NAME)

$(NAME) : $(OBJECTS)
						gcc -c $(FILES) $(FLAGS) -I $(INCLUDE)
						ar rc $(NAME) $(OBJECTS)

clean : 
			/bin/rm -f $(OBJECTS)

fclean : clean
			/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
