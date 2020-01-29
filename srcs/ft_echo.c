/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:41:06 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/29 14:56:33 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_echo(char *cmd)
{
	char	*new;

	new = ft_substr(cmd, 5, ft_strlen(cmd));
	write(1, new, ft_strlen(new));
	write(1, "\n", 1);
}
