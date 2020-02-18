/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:17:01 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/18 15:18:59 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_export_error(char *str)
{
	write(2, "export: not a valid identifier: ", 32);
	ft_putendl_fd(str, 2);
}
