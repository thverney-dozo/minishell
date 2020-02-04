/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:58:56 by thverney          #+#    #+#             */
/*   Updated: 2020/02/04 03:29:37 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

int main()
{
	int pid;

	pid = fork();
	if (pid)
	{
		printf("[%i]PARENT!\n", getpid());
	}
	else
	{
		printf("[%i]CHILD!\n", getpid());
		execve("/bin/ls", (char *[3]){"/bin/ls", "-la", 0}, (char*[2]){"0=cheat", 0});
		printf("FINI\n");
	}
}