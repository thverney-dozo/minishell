/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:23:26 by thverney          #+#    #+#             */
/*   Updated: 2020/02/26 03:43:01 by thverney         ###   ########.fr       */
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
