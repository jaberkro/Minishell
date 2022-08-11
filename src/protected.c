/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 17:25:30 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/10 18:27:34 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	protected_pipe(int fd[2])
{
	if (pipe(fd) < 0)
		error_exit("Pipe failed", 1);
}

int	protected_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 1);
	return (pid);
}

void	protected_dup2s(int readfd, int writefd)
{
	if (dup2(readfd, STDIN_FILENO) < 0)
		error_exit("Dup2 failed", 1);
	if (dup2(writefd, STDOUT_FILENO) < 0)
		error_exit("Dup2 failed", 1);
}

/**
 * @brief ft_split and exits if malloc failed
 * 
 * @param to_split 	the string to be splitted by ft_split
 * @param delimiter the delimiter to split on
 * @return char** 	the splitted string, already checked if malloc failed
 */
char	**protected_split(char *to_split, char delimiter)
{
	char	**output;

	output = ft_split(to_split, delimiter);
	if (output == NULL)
		error_exit("Malloc failed", 1);
	return (output);
}

/**
 * @brief splits a string on delimiter and returns one of its indexes. frees the
 * splitted string
 * 
 * @param to_split 	the string to be splitted
 * @param delimiter the delimiter to split the string on
 * @param index 	the index of the part of the splitted string to be sent back
 * @return char* 	the index of the splitted string, splitted on delimiter
 */
char	*protected_split_grep_one(char *to_split, char delimiter, int index)
{
	char	*output;
	char	**splitted;
	int		i;

	i = 0;
	splitted = protected_split(to_split, delimiter);
	output = ft_strdup(splitted[index]);
	if (output == NULL)
		return (NULL);
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (output);
}
