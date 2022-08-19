/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 10:14:59 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

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
			{
				return (error_return(parts[i].in[j], -1));
			}
			readfd = open(parts[i].in[j], O_RDONLY);
			if (readfd < 0)
				return (error_return(parts[i].in[j], -1));
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
			if (fd < 0)
				return (error_return(parts[i].out[j], -1));
			j++;
		}
	}
	else if (i == max - 1)
	{
		close(fd);
		fd = dup(1);
		if (fd == -1)
			error_exit("dup failed", 1);
	}
	return (fd);
}

/**
 * @brief updates read and write fd, checks if there is a command to execute.
 * Uses find_builtin_function to execute a builtin function
 * 
 * @param i 		index of the part to execute
 * @param readfd 	the fd to read from
 * @param fd 		a pipe. fd[1] is the writefd to update
 * @param parts 	the array of parts
 * @return int 	-1 if everything went right and no builtin function was executed.
 * Otherwise return the exit_code to exit with
 */
int	dup2_builtin(int i, int *readfd, int (*fd)[2], t_part_split *parts)
{
	int	max;

	max = 0;
	while (parts[max].cmd)
		max++;
	*readfd = update_readfd(i, *readfd, parts);
	if (*readfd == -1)
		return (1);
	(*fd)[1] = update_writefd(i, max, (*fd)[1], parts);
	if ((*fd)[1] == -1)
		return (1);
	if (!parts[i].cmd[0] || ft_strncmp(parts[i].cmd[0], "", 1) == 0)
		return (0);
	protected_dup2s(*readfd, (*fd)[1]);
	close(*readfd);
	close((*fd)[1]);
	close((*fd)[0]);
	return (find_builtin_function(parts[i].cmd, max));
}

/**
 * @brief save the standard in and output, go to dup2_builtin and reset the 
 * stdin and stdout afterwards
 * 
 * @param i 		the index of the part to execute
 * @param readfd 	the fd to read from
 * @param fd		a pipe. fd[1] is the writefd to update
 * @param parts 	the array of parts
 * @return int -1 if everything went right and no builtin function was executed.
 * Otherwise return the exit_code to exit with
 */
int	execute_builtin_reset(int i, int *readfd, int (*fd)[2], t_part_split *parts)
{
	int	standard_in;
	int	standard_out;
	int	exit_code;

	standard_in = dup(0);
	standard_out = dup(1);
	if (standard_in == -1 || standard_out == -1)
		error_exit("dup failed", 1);
	exit_code = dup2_builtin(i, readfd, fd, parts);
	protected_dup2s(standard_in, standard_out);
	close(standard_in);
	close(standard_out);
	return (exit_code);
}

/**
 * @brief executes the commands per part, returns pid of inner child
 * 
 * @param i 		index of the current part we execute
 * @param max 		amount of parts
 * @param readfd	the fd to start reading from
 * @param parts		array of t_part_split
 * @return int 		pid of inner child
 */
void	executer(int i, int max, int readfd, t_part_split *parts)
{
	int		fd[2];
	char	*path;
	int		exit_code;
	// struct sigaction	sa;

	// sa.sa_handler = &sig_handler_exec;
	protected_pipe(fd);
	exit_code = -1;
	if (max == 1)
		exit_code = execute_builtin_reset(i, &readfd, &fd, parts);
	// sigaction(SIGINT, &sa, NULL);
	g_info.pids[i] = protected_fork();
	if (g_info.pids[i] == 0)
	{
		suppress_output_terminal();
		if (exit_code == -1)
			exit_code = dup2_builtin(i, &readfd, &fd, parts);
		if (exit_code != -1)
			exit(exit_code);
		path = command_in_paths(parts[i].cmd[0], g_info.paths);
		if (execve(path, parts[i].cmd, g_info.env) < 0)
			error_exit("execve failed", 1);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		executer(i + 1, max, fd[0], parts);
}
