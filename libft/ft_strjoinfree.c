/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:43:26 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/10 14:46:48 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int a)
{
	int		len1;
	int		len2;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dest = (char*)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (s1 && s1[i])
		dest[j++] = s1[i++];
	if (a == 1 || a == 3)
		ft_clear(&s1);
	i = 0;
	while (s2 && s2[i])
		dest[j++] = s2[i++];
	if (a == 2 || a == 3)
		ft_clear(&s2);
	dest[j] = '\0';
	return (dest);
}
