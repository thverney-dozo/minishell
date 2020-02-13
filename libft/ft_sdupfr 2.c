/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdupfr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:44:58 by aeoithd           #+#    #+#             */
/*   Updated: 2020/01/16 01:04:34 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*sdupfr(char *s1, size_t n)
{
	int		i;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	dest[i] = '\0';
	n == 1 ? free(s1) : 1;
	return (dest);
}
