/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:16:21 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 16:52:32 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
	this is a file that will help with the understanding of forks, without using the wait and waitpid functions

	reminder: we cannot use getpid in minishell
*/

int main(void)
{
	pid_t	pid;
	int a = 5;
	int *b;

	pid = fork();
	b = &a;
	printf("valor inicial de a %i\n", a);
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("CHILD PROCESS  #PID %d\n", getpid());
		a = 10;
		printf("valor child de a %i\n", a);
		// printf("    #PID_VARIABLE = %d\n", pid);
	}
	else
	{
		wait(NULL);
		printf("PARENT PROCESS #PID %d\n", getpid());
		printf("    #PID_VARIABLE = %d\n", pid);
	}
	printf("b %i\n", *b);
}

/*
	here, the result is that the parent process is executed first, and then the child process is executed
*/
