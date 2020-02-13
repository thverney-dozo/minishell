/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:49:39 by thverney          #+#    #+#             */
/*   Updated: 2019/10/18 15:47:33 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		f_c(char const *str, char c)
{
	int i;

	i = 0;
	while (*str != c && *str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

int		nb_w(char const *s, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			j++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;
	int		j;

	if (!s || !c)
		return (NULL);
	i = -1;
	words = nb_w(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb_w(s, c) + 1))))
		return (NULL);
	while (++i < words)
	{
		j = 0;
		while (*s == c && *s != '\0')
			s++;
		if (!(tab[i] = (char*)malloc(sizeof(char) * (f_c(s, c) + 1))))
			return (NULL);
		while (*s != c && *s != '\0')
			tab[i][j++] = *s++;
		tab[i][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
