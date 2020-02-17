/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:39:39 by thverney          #+#    #+#             */
/*   Updated: 2020/02/16 23:58:17 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		next_space(char *str, int i)
{
	while (str[i] && str[i] > 32)
		i++;
	return (i);
}

int		next_none_space(char *str, int i)
{
	while (str[i] && str[i] < 33)
		i++;
	return (i);
}
