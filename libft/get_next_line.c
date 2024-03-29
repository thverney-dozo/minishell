/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:13:04 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/26 01:59:28 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero_gnl(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char*)s = '\0';
		s++;
		i++;
	}
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*result;

	if (count == 0 || size == 0)
		return (NULL);
	if (!(result = malloc(count * size)))
		return (NULL);
	ft_bzero_gnl(result, (size * count));
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static char		*result[MAX_FD];
	char			*buff;
	int				r;

	if ((r = 1) && (BUFFER_SIZE == 0 || !line || fd < 0))
		return (-1);
	if (!result[fd])
		if (!(result[fd] = ft_calloc_gnl(sizeof(char), 1)))
			return (-1);
	if (!(buff = ft_calloc_gnl(sizeof(char), (BUFFER_SIZE + 1))))
		return (-1);
	while (r != 0 && is_n(result[fd]) == -1)
	{
		r = read(fd, buff, BUFFER_SIZE);
		(ft_strchr(buff, '\n') == NULL) ? write(1, "  \e[D\e[D", 9) : 0;
		if ((r == 0 && *result[0]) || (r < 0))
			return ((r == 0 && *result[0]) ? 2 : -1);
		buff[r] = '\0';
		result[fd] = ft_strjoin_gnl(result[fd], buff, r);
	}
	*line = ft_result(result[fd]);
	free(buff);
	result[fd] = ft_next(result[fd], r);
	return (r == 0 ? 0 : 1);
}
