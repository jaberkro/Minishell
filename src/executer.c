/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/19 18:40:23 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	error_exit(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

void	print_parts(t_part *parts)
{
	int	i;

	i = 0;
	while (parts[i].str)
	{
		printf("%c %s %c\n", parts[i].lb, parts[i].str, parts[i].rb);
		i++;
	}
}

void	print_part(t_part part)
{
	printf("%c %s %c\n", part.lb, part.str, part.rb);
}

int	executer(int i, int max, int readfd, t_part *parts)
{
	int		fd[2];
	int		pid;
	char	**command;

	readfd = 1;
	protected_pipe(fd);
	pid = protected_fork();
	if (pid == 0)
	{
		fd[1] = 0;
		protected_dup2s(fd[1], readfd);
		close(readfd);
		close(fd[0]);
		close(fd[1]);
		print_part(parts[i]);
		//command &paths
		if (execve("/bin/cat", command, g_env_variables) < 0)
			error_exit("Execve failed", 1);
	}
	close(readfd);
	close(fd[0]);
	close(fd[1]);
	if (i < max)
			pid = executer(i + 1, max, readfd, parts);
	return (pid);
}
