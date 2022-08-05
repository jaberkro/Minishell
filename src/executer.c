/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/05 10:18:45 by jaberkro      ########   odam.nl         */
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
	char	*return_value;

	return_value = ft_strjoin(ft_strdup("?="), ft_itoa(exit_code));
	// printf("write_exit[%s]\n", return_value);
	set_env_variable(return_value);
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	write_exit_argument(char *argument, char *message, int exit_code)
{
	char	*return_value;

	return_value = ft_strjoin(ft_strdup("?="), ft_itoa(exit_code));
	// printf("write_exit_argument[%s]\n", return_value);
	set_env_variable(return_value);
	if (argument)
		write(2, argument, ft_strlen(argument));
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	error_exit(char *message, int exit_code)
{
	char	*return_value;

	return_value = ft_strjoin(ft_strdup("?="), ft_itoa(exit_code));
	// printf("error_exit[%s]\n", return_value);
	set_env_variable(return_value);
	perror(message);
	exit(exit_code);
}

int	update_readfd(int i, int readfd, t_part_split *parts)
{
	int		j;

	j = 0;
	if (parts[i].in && parts[i].in[0])
	{
		while (parts[i].in[j])
		{
			close(readfd);
			if (access(parts[i].in[j], F_OK) == -1 || access(parts[i].in[j], R_OK) == -1)
				error_exit(parts[i].in[j], 1);
			readfd = open(parts[i].in[j], O_RDONLY);
			if (readfd < 0)
				error_exit(parts[i].in[j], 1);
			j++;
		}
	}
	return (readfd);
}

int	update_writefd(int i, int max, int writefd, t_part_split *parts)
{
	int		j;

	j = 0;
	if (parts[i].out_r && parts[i].out_r[0])
	{
		while (parts[i].out[j])
		{
			if (parts[i].out_r[j] == '>')
				writefd = open(parts[i].out[j], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else
				writefd = open(parts[i].out[j], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (writefd < 0)
				error_exit(parts[i].out[j], 1);
			j++;
		}
	}
	else if (i == max - 1)
	{
		writefd = dup(STDOUT_FILENO);
	}
	return (writefd);
}

int	executer(int i, int max, int readfd, t_part_split *parts)
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
		protected_dup2s(readfd, fd[1]);
		close(readfd);
		close(fd[0]);
		close(fd[1]);
		// printf("first command: %s\n", parts[i].cmd[0]);
		find_builtin_function(parts[i].cmd, max);
		path = command_in_paths(parts[i].cmd[0], g_info.paths);
		// printf("path: %s\n", path);
		if (execve(path, parts[i].cmd, g_info.env) < 0)
			error_exit("Execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
