/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/08 11:35:04 by jaberkro      ########   odam.nl         */
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

void	execute_export(char **commands)
{
	int	i;

	i = 1;
	//zonder argumenten de gesorteerde versie printen
	while (commands[i])
	{
		if (ft_strchr(commands[i], '='))
		{
			printf("exporting %s...\n", commands[i]);
			if (!set_env_variable(commands[i])) // werkt niet
				printf("exporting %s failed\n", commands[i]);
		}
		i++;
	}
	exit(0);
}

void	execute_cd(char *command)
{
	printf("changing to directory %s...\n", command);
	exit(0);
}

void	execute_pwd(char **commands)
{
	if (execve("/bin/pwd", commands, g_info.env) < 0)
		error_exit("Execve failed", 1);
	exit(0);
}

void	execute_env(void)
{
	int	i;

	i = 0;
	while (g_info.env[i])
	{
		printf("%s\n", g_info.env[i]);
		i++;
	}
	exit(0);
}

void	execute_echo(char **commands)
{
	if (execve("/bin/echo", commands, g_info.env) < 0)
		error_exit("Execve failed", 1);
}

void	find_builtin_function(char **commands)
{
	if (!commands || !commands[0])
		return ;
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		execute_echo(commands);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		execute_pwd(commands);
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		execute_cd(commands[1]);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		execute_export(commands);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		execute_unset(commands[1]);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		execute_env();
	if (ft_strncmp(commands[0], "exit", 5) == 0)
		exit(0);
}
