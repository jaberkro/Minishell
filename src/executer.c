/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 18:47:10 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * @brief updates the readfd 
 * 
 * @param i 		index of which part between pipes we look at
 * @param readfd 	open fd from last pipe. Initialized as 0
 * @param parts 	array of t_part_split
 * @return int 		updated readfd
 */
int	update_readfd(int i, int max, int readfd, t_part_split *parts)
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
			{
				if (max != 1)
					error_exit(parts[i].in[j], 1);
				write(STDOUT_FILENO, "mickeyshell: ", 13);
				perror(parts[i].in[j]);
				return (-1);
			}
			readfd = open(parts[i].in[j], O_RDONLY);
			if (readfd < 0 && max != 1)
			{
				error_exit(parts[i].in[j], 1);
			}
			else if (readfd < 0)
			{
				write(STDOUT_FILENO, "mickeyshell: ", 13);
				perror(parts[i].in[j]);
				return (-1);
			}
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
 * @param fd		write fd from last pipe. Initialized as 1 
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
			if (fd < 0 && max != 1)
				error_exit(parts[i].out[j], 1);
			else if (fd < 0)
			{
				write(STDOUT_FILENO, "mickeyshell: ", 13);
				perror(parts[i].out[j]);
				return (-1);
			}
			j++;
		}
	}
	else if (i == max - 1)
	{
		close(fd);
		fd = dup(1);
		if (fd == -1)
			error_exit("mickeyshell: dup failed", 1);
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
	int		standard_readfd;
	int		standard_writefd;

	pid = 0;
	protected_pipe(fd);
	exit_code = -1;
	if (max == 1)
	{
		standard_readfd = dup(0);
		standard_writefd = dup(1);
		readfd = update_readfd(i, max, readfd, parts);
		if (readfd == -1)
			exit_code = 1;
		if (exit_code == -1)
			fd[1] = update_writefd(i, max, fd[1], parts);
		if (fd[1] == -1)
			exit_code = 1;
		if (!parts[i].cmd || !parts[i].cmd[0])
			exit_code = 0;
		if (exit_code == -1)
		{
			protected_dup2s(readfd, fd[1]);
			close(fd[0]);
			close(fd[1]);
			close(readfd);
			exit_code = find_builtin_function(parts[i].cmd, max);
			protected_dup2s(standard_readfd, standard_writefd);
			close(standard_readfd);
			close(standard_writefd);
		}
	}
	pid = protected_fork();
	if (pid == 0)
	{
		if (exit_code != -1)
			exit(exit_code);
		readfd = update_readfd(i, max, readfd, parts);
		fd[1] = update_writefd(i, max, fd[1], parts);
		protected_dup2s(readfd, fd[1]);
		close(fd[0]);
		close(fd[1]);
		close(readfd);
		if (max != 1)
			exit_code = find_builtin_function(parts[i].cmd, max);
		if (exit_code != -1)
			exit(exit_code);
		if (!parts[i].cmd[0] || ft_strncmp(parts[i].cmd[0], "", 1) == 0)
			exit(0);
		path = command_in_paths(parts[i].cmd[0], g_info.paths);
		if (execve(path, parts[i].cmd, g_info.env) < 0)
			error_exit("mickeyshell: execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
