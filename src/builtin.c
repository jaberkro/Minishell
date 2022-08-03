/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/03 13:40:32 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	execute_unset(char *command)
{
	printf("unsetting %s...\n", command);
	exit(0);
}

void	execute_export(char *command, int max)
{
	if (ft_strchr(command, '=') && max == 1)
		printf("exporting %s...\n", command);
	exit(0);
}

void	execute_cd(char *command)
{
	printf("changing to directory %s...\n", command);
	exit(0);
}

void	find_builtin_function(char *command, int max)
{
	char	*first_command;

	first_command = protected_split(command, ' ')[0];
	if (ft_strncmp(first_command, "cd", 3) == 0)
		execute_cd(protected_split(command, ' ')[1]);
	if (ft_strncmp(first_command, "export", 7) == 0)
		execute_export(protected_split(command, ' ')[1], max);
	if (ft_strncmp(first_command, "unset", 6) == 0)
		execute_unset(protected_split(command, ' ')[1]);
	if (ft_strncmp(first_command, "exit", 5) == 0)
		exit(0);
}
