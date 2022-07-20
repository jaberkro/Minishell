/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 17:25:30 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/19 17:44:04 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	protected_pipe(int fd[2])
{
	if (pipe(fd) < 0)
		error_exit("Pipe failed", 1);
}

int	protected_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 1);
	return (pid);
}

void	protected_dup2s(int writefd, int readfd)
{
	if (dup2(writefd, STDOUT_FILENO) < 0)
		error_exit("Dup2 failed", 1);
	if (dup2(readfd, STDIN_FILENO) < 0)
		error_exit("Dup2 failed", 1);
}