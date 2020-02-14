/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloubie <anloubie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:55:53 by antoine           #+#    #+#             */
/*   Updated: 2020/02/14 11:59:11 by anloubie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_num_var(t_env *env)
{
	t_var	*tmp;
	int		count;

	tmp = env->var;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int			ft_buflen(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

void		ft_exp_aff(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(dest[i], 1);
		free(dest[i]);
		i++;
	}
	free(dest);
}

void		ft_exp_sort(char **dest)
{
	int		i;
	char	*tmp;

	i = 0;
	while (dest[i] && dest[i + 1])
	{
		if (ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			tmp = dest[i + 1];
			dest[i + 1] = dest[i];
			dest[i] = tmp;
			i = 0;
		}
		else
			i++;
	}
	ft_exp_aff(dest);
}

void		env_malloc(t_env *env)
{
	int		len;
	int		i;
	char	**dest;
	t_var	*tmp;
	char	*temp;

	len = ft_num_var(env);
	tmp = env->var;
	i = 0;
	if (!(dest = (char**)malloc(sizeof(char*) * (len + 1))))
		return ;
	while (tmp)
	{
		if (!(dest[i] = ft_strjoin(tmp->name, "=\"")))
			return ;
		temp = dest[i];
		if (!(dest[i] = ft_strjoinfree(temp, tmp->value, 1)))
			return ;
		temp = dest[i];
		if (!(dest[i++] = ft_strjoinfree(temp, "\"", 1)))
			return ;
		tmp = tmp->next;
	}
	dest[i] = NULL;
	ft_exp_sort(dest);
}
