/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/10 14:42:55 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * @brief writes a message to stderr and exits. 
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
	write(2, message, ft_strlen(message));
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
	if (argument)
		write(2, argument, ft_strlen(argument));
	write(2, message, ft_strlen(message));
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
 * @param writefd	write fd from last pipe. Initialized as 1 
 * @param parts 	array of t_part_split
 * @return int 
 */
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
		if (writefd == -1)
			error_exit("Dup failed", 1);
	}
	return (writefd);
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
	int		executed;

	pid = 0;
	executed = 0;
	protected_pipe(fd);
	if (max == 1)
	{
		readfd = update_readfd(i, readfd, parts);
		fd[1] = update_writefd(i, max, fd[1], parts);
		executed += find_builtin_function(parts[i].cmd, max);
	}
	pid = protected_fork();
	if (pid == 0)
	{
		if (max != 1)
		{
			readfd = update_readfd(i, readfd, parts);
			fd[1] = update_writefd(i, max, fd[1], parts);
		}
		protected_dup2s(readfd, fd[1]);
		close(readfd);
		close(fd[0]);
		close(fd[1]);
		if (max != 1)
			executed += find_builtin_function(parts[i].cmd, max);
		if (executed != 0)
			exit(0); //moet dit altijd 0 zijn? Denk het wel
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
