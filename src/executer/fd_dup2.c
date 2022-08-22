/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_dup2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:40:36 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 16:47:04 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

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
			protected_close(readfd);
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
			protected_close(fd);
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
		protected_close(fd);
		fd = dup(1);
		if (fd == -1)
			error_exit("dup", 1);
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
	int	exit_code;

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
	if (max != 1)
		protected_close(*readfd);
	if (max != 1)
		protected_close((*fd)[1]);
	protected_close((*fd)[0]);
	exit_code = find_builtin_function(parts[i].cmd, max);
	return (exit_code);
}
