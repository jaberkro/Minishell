/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 17:53:31 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief prints the current working directory
 * 
 * @param commands 	not used but sent from jumptable
 * @param max 		not used but sent from jumptable
 * @return int 
 */
int	execute_pwd(char **commands, int max)
{
	char	cwd[256];

	(void)max;
	(void)commands;
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
