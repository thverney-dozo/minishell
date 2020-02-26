/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:08:34 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 14:26:58 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(ret = malloc(sizeof(char))))
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))) || !s)
		return (NULL);
	i = 0;
	while (len > 0 && s[i + start])
	{
		ret[i] = (char)s[i + start];
		len--;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
