/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 15:26:08 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

/**
 * @brief Set the exit_code in the env variables
 * 
 * @param exit_code the exit code of the builtin function that was executed
 * @return int 		the exit code of the builtin function that was executed
 */
int	set_exit_code(int exit_code)
{
	char	*exit_num;
	char	*exit_str;

	if (exit_code != -1)
	{
		exit_num = ft_itoa(exit_code);
		if (exit_num == NULL)
			error_exit("malloc", 1);
		exit_str = ft_strjoin("?=", exit_num);
		set_env_variable(exit_str);
		free(exit_str);
		free(exit_num);
	}
	return (exit_code);
}

/**
 * @brief jumptable to find and execute builtin functions 
 * 
 * @param commands 	the commands to be passed to builtin function
 * commands[0] is the command to be found in the jumptable
 * @param max 		the amount of parts, to be passed to the builtin functions
 * @return int 		-1 if it is not a builtin function, otherwise the exit code
 */
int	find_builtin_function(char **commands, int max)
{
	int				i;
	const t_builtin	builtins[] = {
	{"cd", &execute_cd},
	{"echo", &execute_echo},
	{"env", &execute_env},
	{"exit", &execute_exit},
	{"export", &execute_export},
	{"pwd", &execute_pwd},
	{"unset", &execute_unset},
	{NULL, NULL}
	};

	i = 0;
	while (builtins[i].key)
	{
		if (ft_strncmp(commands[0], builtins[i].key, \
		ft_strlen(builtins[i].key) + 1) == 0)
		{
			return (set_exit_code(builtins[i].func(commands, max)));
		}
		i++;
	}
	return (-1);
}
