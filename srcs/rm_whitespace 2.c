/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:23:26 by thverney          #+#    #+#             */
/*   Updated: 2020/02/04 05:28:04 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_space(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] < 33)
			i++;
		while (str[i++] > 32)
			j++;
		if (str[i++] < 33)
			j++;
	}
}

char	*rm_whitespace(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = count_space(str) + 1;
	if (!(dest = malloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] < 33)
			i++;
		while (str[i] > 32)
			dest[j++] = str[i++];
		if (str[i++] < 33)
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (dest);
}
