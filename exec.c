/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:58:56 by thverney          #+#    #+#             */
/*   Updated: 2020/02/07 00:57:45 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <wait.h>

// #define READ_PIPE 0
// #define WRITE_PIPE 1

int main(void){
    
    pid_t returnPID;

    int thePipe[2];

    if (pipe(thePipe) < 0 || (returnPID = fork()) < 0)
        exit(EXIT_FAILURE);

    if (returnPID == 0)
	{
        close(thePipe[0]);
        dup2(thePipe[1], 1);    
        printf("Never attribute to malice that which can be adequately explained by stupidity.\n");
    }
	else
	{
        close(thePipe[1]);
        // wait(NULL);
        printf("In parent process:");
        char buffer[256];
        read(thePipe[0], buffer, 256);
        printf("%s\n", buffer);    
    }

    return 0;

}