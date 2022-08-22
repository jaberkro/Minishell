/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 17:25:30 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 15:51:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief close, exit if close fails. (in theory close only fails if you pass an 
 * invalid or already freed fd to it)
 * 
 * @param fd the fd to close
 */
void	protected_close(int fd)
{
	if (close(fd) < 0)
		error_exit("close", 1);
}

/**
 * @brief dup2 twice for STDIN and STDOUT and in case one of them fails exit
 * 
 * @param readfd 	the fd to dup2 with STDIN_FILENO
 * @param writefd 	the fd to dup2 with STDOUT_FILENO
 */
void	protected_dup2s(int readfd, int writefd)
{
	if (dup2(readfd, STDIN_FILENO) < 0)
		error_exit("dup2", 1);
	if (dup2(writefd, STDOUT_FILENO) < 0)
		error_exit("dup2", 1);
}

/**
 * @brief ft_split and exit if malloc failed
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
		error_exit("malloc", 1);
	return (output);
}

/**
 * @brief splits a string on delimiter and returns one of its indexes. Frees the
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
		error_exit("malloc", 1);
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (output);
}
