/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:05:53 by thverney          #+#    #+#             */
/*   Updated: 2020/01/29 14:39:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] < 33 && str[i] != '\0')
			i++;
		if (str[i] > 32)
			j++;
		while (str[i] > 32)
			i++;
	}
	return (j);
}

int		count_c(char *str)
{
	int i;

	i = 0;
	while (str[i] > 32)
		i++;
	return (i);
}

char	**split_wh_sp(char *str)
{
	int		i;
	char	**tab;
	int		j;
	int		words;

	words = ft_count_words(str);
	if (!(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*str < 33 && *str != '\0')
			str++;
		if (!(tab[i] = (char*)malloc(sizeof(char) * (count_c(str) + 1))))
			return (NULL);
		j = 0;
		while (*str > 32)
			tab[i][j++] = *str++;
		tab[i][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
