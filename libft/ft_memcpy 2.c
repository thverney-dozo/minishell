/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:26:11 by thverney          #+#    #+#             */
/*   Updated: 2019/10/16 19:28:12 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char*)dst;
	s2 = (char*)src;
	if (src == 0 && dst == 0)
		return (dst);
	if (src == 0)
		src++;
	if (dst == 0)
		dst++;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}
