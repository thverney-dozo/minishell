/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:19:12 by thverney          #+#    #+#             */
/*   Updated: 2019/10/16 19:30:05 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int i;
	unsigned int k;

	if (!(*needle))
		return ((char*)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		k = 0;
		while (needle[k] == haystack[i + k] && i + k < len)
		{
			if (needle[k + 1] == '\0')
			{
				return ((char*)haystack + i);
			}
			k++;
		}
		i++;
	}
	return (NULL);
}
