/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/12 11:04:46 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * @brief writes a message to stderr and exits
 * 
 * @param message 	the message to print
 * @param exit_code the code to exit with
 */
void	write_exit(char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	write(STDERR_FILENO, "mickeyshell: ", 13);
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(exit_code);
}

/**
 * @brief writes a message with an argument in front of it to stderr, exits
 * 
 * @param argument	the 'topic' the message is about
 * @param message 	the message to be printed (about the variable)
 * @param exit_code the code to exit with
 */
void	write_exit_argument(char *argument, char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	write(STDERR_FILENO, "mickeyshell: ", 13);
	if (argument)
		write(STDERR_FILENO, argument, ft_strlen(argument));
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(exit_code);
}

/**
 * @brief uses perror to print an error message and exits
 * 
 * @param message 	the message to given to perror
 * @param exit_code the code to exit with
 */
void	error_exit(char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	perror(message);
	exit(exit_code);
}

/**
 * @brief updates the readfd 
 * 
 * @param i 		index of which part between pipes we look at
 * @param readfd 	open fd from last pipe. Initialized as 0
 * @param parts 	array of t_part_split
 * @return int 		updated readfd
 */
int	update_readfd(int i, int readfd, t_part_split *parts)
{
	int		j;

	j = 0;
	if (parts[i].in && parts[i].in[0])
	{
		while (parts[i].in[j])
		{
			close(readfd);
			if (access(parts[i].in[j], F_OK) == -1 || \
			access(parts[i].in[j], R_OK) == -1)
				error_exit(parts[i].in[j], 1);
			readfd = open(parts[i].in[j], O_RDONLY);
			if (readfd < 0)
				error_exit(parts[i].in[j], 1);
			j++;
		}
	}
	return (readfd);
}

/**
 * @brief updates the writefd
 * 
 * @param i 		index of which part between pipes we look at
 * @param max 		amount of parts in total
 * @param fd	write fd from last pipe. Initialized as 1 
 * @param parts 	array of t_part_split
 * @return int 
 */
int	update_writefd(int i, int max, int fd, t_part_split *parts)
{
	int		j;

	j = 0;
	if (parts[i].out_r && parts[i].out_r[0])
	{
		while (parts[i].out[j])
		{
			close(fd);
			if (parts[i].out_r[j] == '>')
				fd = open(parts[i].out[j], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else
				fd = open(parts[i].out[j], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
				error_exit(parts[i].out[j], 1);
			j++;
		}
	}
	else if (i == max - 1)
	{
		close (fd);
		fd = dup(STDOUT_FILENO);
		if (fd == -1)
			error_exit("Dup failed", 1);
	}
	return (fd);
}

/**
 * @brief executes the commands per part, returns pid of inner child
 * 
 * @param i 		the current part we execute
 * @param max 		amount of parts
 * @param readfd	the fd to start reading from
 * @param parts		array of t_part_split
 * @return int 		pid of inner child
 */
int	executer(int i, int max, int readfd, t_part_split *parts)
{
	int		fd[2];
	int		pid;
	char	*path;
	int		exit_code;

	pid = 0;
	exit_code = 0;
	protected_pipe(fd);
	if (max == 1)
	{
		int tmpreadfd = dup(0);
		int tmpwritefd = dup(1);
		readfd = update_readfd(i, readfd, parts);
		fd[1] = update_writefd(i, max, fd[1], parts);
		protected_dup2s(readfd, fd[1]);
		close(fd[0]);
		close(fd[1]);
		close(readfd);
		exit_code = find_builtin_function(parts[i].cmd, max);
		dup2(tmpreadfd, STDIN_FILENO);
		dup2(tmpwritefd, STDOUT_FILENO);
		close(tmpreadfd);
		close(tmpwritefd);
	}
	pid = protected_fork();
	if (pid == 0)
	{
		if (exit_code == -1)
		{
			readfd = update_readfd(i, readfd, parts);
			fd[1] = update_writefd(i, max, fd[1], parts);
			protected_dup2s(readfd, fd[1]);
			close(fd[0]);
			close(fd[1]);
			close(readfd);
			if (max != 1)
				exit_code = find_builtin_function(parts[i].cmd, max);
		}
		if (exit_code != -1)
			exit(exit_code);
		path = command_in_paths(parts[i].cmd[0], g_info.paths);
		if (execve(path, parts[i].cmd, g_info.env) < 0)
			error_exit("Execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
