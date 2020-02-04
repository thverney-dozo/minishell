/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:55:18 by anloubie          #+#    #+#             */
/*   Updated: 2020/02/04 01:32:51 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd_two(char *tmp, char *path, int i)
{
		while (*path < 33 && *path != '\0')
			path++;
		tmp = path;
		i = 0;
		while (*tmp > 32 && *tmp++)
			i++;
		while (*tmp < 33 && *tmp != '\0' && *tmp != ';' && *tmp != '|')
			tmp++;
		if (*tmp != '\0' && *tmp != ';' && *tmp != '|')
		{
			write(1, "cd: string not in pwd: ", 23);
			write(1, path, i);
			write(1, "\n", 1);
		}
		else
			chdir(path);
}

void        ft_cd(char *path)
{
	char	*tmp;

	tmp = path;
	while (*tmp < 33 && *tmp != '\0' && *tmp != ';' && *tmp != '|')
		tmp++;
	if (*tmp == '\0' || *tmp == ';' || *tmp == '|')
	{
		tmp = "/Users/thverney";	
		chdir(tmp);
	}
	else
		ft_cd_two(tmp, path, 0);
}
