/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 15:33:16 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	find_builtin_function(char **commands, int max)
{
	int		status;
	char	*status_num;
	char	*status_str;

	status = -1;
	if (!commands || !commands[0])
		return (0);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		status = execute_pwd();
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		status = execute_cd(commands[1]);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		status = execute_export(commands);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		status = execute_unset(commands[1]);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		status = execute_env();
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		status = execute_echo(commands);
	if (ft_strncmp(commands[0], "exit", 5) == 0)
		execute_exit(commands, max);
	if (max != 1 && status != -1)
		exit(status);
	status_num = ft_itoa(status);
	if (status_num == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	if (status != -1)
	{
		status_str = ft_strjoin("?=", status_num);
		set_env_variable(status_str);
		free(status_str);
	}
	free(status_num);
	return (status);
}
