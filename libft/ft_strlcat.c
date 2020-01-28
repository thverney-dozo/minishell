/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:58:08 by thverney          #+#    #+#             */
/*   Updated: 2019/10/16 19:29:38 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*dest;
	const char	*source;
	size_t		len;
	size_t		size;

	dest = (const char*)dst;
	source = src;
	len = dstsize;
	while (len-- != 0 && *dst != '\0')
		dst++;
	size = dst - dest;
	len = dstsize - size;
	if (len-- == 0)
		return (size + ft_strlen(src));
	while (*src != '\0')
	{
		if (len != 0)
		{
			*dst++ = *src;
			len--;
		}
		src++;
	}
	*dst = '\0';
	return (size + (src - source));
}
