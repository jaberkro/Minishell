/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 18:34:02 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	update_writefd(int i, int writefd, t_part *parts)
{
	if (parts[i].out_r == '>' || parts[i].out_r == ']')
	{
		if (parts[i].out_r == '>')
			writefd = open(parts[i].out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			writefd = open(parts[i].out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (writefd < 0)
			error_exit(parts[i].out, 1);
	}
	// else
	// 	writefd = 1;
	return (writefd);
}

static char	*make_path(char *path)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(path);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	tmp = command;
	command = ft_strjoin(command, "/");
	free(tmp);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	return (command);
}

char	*command_in_paths(char	*argument, char **paths)
{
	int		i;
	char	*command;
	char	*tmp;

	i = 0;
	if (access(argument, X_OK) != -1)
		return (argument);
	if (!paths)
		write_exit_argument(argument, ": No such file or directory\n", 127);
	if (!argument)
		write_exit(": command not found\n", 127);
	while (paths && paths[i])
	{
		command = make_path(paths[i]);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("Malloc failed", 1);
		if (access(command, X_OK) != -1)
			return (command);
		free(command);
		i++;
	}
	write_exit_argument(argument, ": command not found\n", 127);
	return (NULL);
}

int	executer(int i, int max, int readfd, t_part *parts)
{
	int		fd[2];
	int		pid;
	char	*path;

	printf("%d\n", i);
	protected_pipe(fd);
	pid = protected_fork();
	if (pid == 0)
	{
		readfd = update_readfd(i, readfd, parts);
		fd[1] = update_writefd(i, fd[1], parts);
		path = command_in_paths(protected_split(parts[i].cmd, ' ')[0], protected_split("/Users/jaberkro/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:~/.dotnet/tools:/Users/jaberkro/.brew/bin", ':'));
		protected_dup2s(fd[1], readfd);
		close(readfd);
		close(fd[0]);
		close(fd[1]);
		if (execve(path, ft_split(parts[i].cmd, ' '), NULL) < 0)
			error_exit("Execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
