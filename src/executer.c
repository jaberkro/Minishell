/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 17:07:41 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	write_exit(char *message, int exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	write_exit_argument(char *argument, char *message, int exit_code)
{
	if (argument)
		write(2, argument, ft_strlen(argument));
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	error_exit(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

int	update_readfd(int i, int readfd, t_part *parts)
{
	if (parts[i].in_r == '<')
	{
		if (access(parts[i].in, F_OK) == -1 || access(parts[i].in, R_OK) == -1)
			error_exit(parts[i].in, 1);
		readfd = open(parts[i].in, O_RDONLY);
		if (readfd < 0)
			error_exit(parts[i].in, 1);
	}
	return (readfd);
}

int	update_writefd(int i, int max, int writefd, t_part *parts)
{
	int	save_out;

	if (parts[i].out_r == '>' || parts[i].out_r == ']')
	{
		if (parts[i].out_r == '>')
			writefd = open(parts[i].out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			writefd = open(parts[i].out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (writefd < 0)
			error_exit(parts[i].out, 1);
	}
	else if (i == max - 1)
	{
		save_out = dup(STDOUT_FILENO);
		writefd = save_out;
	}
	return (writefd);
}

int	executer(int i, int max, int readfd, t_part *parts)
{
	int		fd[2];
	int		pid;
	char	*path;

	protected_pipe(fd);
	pid = protected_fork();
	if (pid == 0)
	{
		readfd = update_readfd(i, readfd, parts);
		fd[1] = update_writefd(i, max, fd[1], parts);
		path = command_in_paths(protected_split(parts[i].cmd, ' ')[0], g_info.paths);
		protected_dup2s(fd[1], readfd);
		close(readfd);
		close(fd[0]);
		close(fd[1]);
		if (execve(path, ft_split(parts[i].cmd, ' '), g_info.env) < 0)
			error_exit("Execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
