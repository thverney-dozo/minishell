/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:22:22 by anloubie          #+#    #+#             */
/*   Updated: 2020/01/29 16:21:13 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_pwd(void)
{
    char    *path;
    char    *ret;
	int		len;
	char	*tmp;
    
	len = 500;
	if (!(path = (char*)malloc(sizeof(char) * len)))
		return ;
    while (!(ret = getcwd(path, len)))
	{
		len += 500;
		tmp = path;
		if (!(path = (char*)malloc(sizeof(char) * len)))
			return ;
		free(tmp);
	}
    write(1, path, ft_strlen(path));
    write(1, "\n", 1);
}
