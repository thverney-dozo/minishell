/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:02:05 by thverney          #+#    #+#             */
/*   Updated: 2019/10/21 19:01:14 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			search(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int len;

	if (!s1 || !set)
		return (NULL);
	while (search(*s1, set) == 1)
		++s1;
	len = ft_strlen(s1);
	while (len && (search(s1[len - 1], set) == 1))
		--len;
	if (len == 0)
		return (ft_strdup("\0"));
	return (ft_substr(s1, 0, len));
}
