/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/05 11:21:08 by jaberkro      ########   odam.nl         */
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
	{
		printf("exporting %s...\n", command);
		if (!set_env_variable(command)) // werkt niet
			printf("exporting %s failed\n", command);
	}
	exit(0);
}

void	execute_cd(char *command)
{
	printf("changing to directory %s...\n", command);
	exit(0);
}

void	find_builtin_function(char **commands, int max)
{

	if (!commands || !commands[0])
		return ;
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		execute_cd(commands[1]);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		execute_export(commands[1], max);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		execute_unset(commands[1]);
	if (ft_strncmp(commands[0], "exit", 5) == 0)
		exit(0);
}
