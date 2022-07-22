/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 18:57:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	execute_export(char *command)
{
	if (!command)
		//show sorted list
	if (ft_strchr(command, '='))
	{
		if (!set_env_variable(command))
			exit(1);
	}
	exit(0);
}

int	find_builtin_function(char *command, int max)
{
	char	*first_command;

	first_command = protected_split(command, ' ')[0];
	if (ft_strncmp(first_command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(first_command, "export", 3) == 0 && max == 1)
		execute_export(protected_split(command, ' ')[1]);
	if (ft_strncmp(first_command, "unset", 3) == 0)
		return (3);
	if (ft_strncmp(first_command, "exit", 3) == 0)
		return (4);
	if (ft_strncmp(first_command, "history", 3) == 0)
		return (5);
	return (0);
}

// void	execute_pwd(void)
// {
// 	printf("%s\n", get_env_variable("PWD="));
// }
