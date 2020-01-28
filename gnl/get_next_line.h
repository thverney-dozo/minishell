/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:30:39 by ade-temm          #+#    #+#             */
/*   Updated: 2020/01/17 06:05:45 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 10
# define MAX_FD 1024

int		get_next_line(int fd, char **line);
char	*ft_strjoin_gnl(char const *s1, char const *s2, int r);
size_t	ft_strlen_gnl(const char *s);
char	*ft_result(char *result);
char	*ft_next(char *ret, int r);
int		is_n(char *buff);
void	*ft_calloc_gnl(size_t count, size_t size);
void	ft_bzero_gnl(void *s, size_t n);

#endif
