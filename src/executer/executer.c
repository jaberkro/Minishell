/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 13:54:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/23 13:31:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

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
static int	builtin_reset(int i, int *readfd, int (*fd)[2], t_part_split *parts)
{
	int	standard_in;
	int	standard_out;
	int	exit_code;

	standard_in = dup(0);
	standard_out = dup(1);
	if (standard_in == -1 || standard_out == -1)
		error_exit("dup", 1);
	exit_code = dup2_builtin(i, readfd, fd, parts);
	protected_dup2s(standard_in, standard_out);
	close(standard_in);
	close(standard_out);
	return (exit_code);
}

/**
 * @brief find the path of the current system function, than execute it
 * 
 * @param i 	the index of what part we should execute the commands now
 * @param parts the parts with the info on what to open and execute
 */
static void	execute_sysfunc(int i, t_part_split *parts)
{	
	char	*path;

	path = command_in_paths(parts[i].cmd[0], g_info.paths);
	if (execve(path, parts[i].cmd, g_info.env) < 0)
		error_exit("execve", 1);
}

/**
 * @brief if exit_code is not -1, exit with this exit code
 * 
 * @param exit_code 	the exit code
 */
static void	check_exit(int exit_code)
{
	if (exit_code != -1)
		exit(exit_code);
}

/**
 * @brief pipe. if pipe fails close the readfd. Otherwise return 1
 * 
 * @param fd_to_pipe 	the fd to pipe
 * @param readfd 		the fd to close if pipe fails
 * @return int -1 if pipe failed, 0 on success
 */
static int	pipe_close_readfd(int (*fd_to_pipe)[2], int readfd)
{
	if (pipe(*fd_to_pipe) < 0)
	{
		close(readfd);
		return (error_return("pipe", -1));
	}
	return (0);
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
pid_t	executer(int i, int max, int readfd, t_part_split *parts)
{
	int					fd[2];
	pid_t				pid;
	int					exit_code;

	set_sigs_exec();
	if (pipe_close_readfd(&fd, readfd) < 0)
		return (-1);
	exit_code = -1;
	if (max == 1)
		exit_code = builtin_reset(i, &readfd, &fd, parts);
	pid = fork();
	if (pid < 0)
		return (error_return("fork", -1));
	if (pid == 0)
	{
		check_exit(exit_code);
		exit_code = dup2_builtin(i, &readfd, &fd, parts);
		check_exit(exit_code);
		execute_sysfunc(i, parts);
	}
	close(readfd);
	close(fd[1]);
	if (i + 1 < max)
		pid = executer(i + 1, max, fd[0], parts);
	return (pid);
}
