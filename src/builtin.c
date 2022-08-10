/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/10 13:19:25 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	execute_env(void)
{
	int	i;

	i = 0;
	while (g_info.env[i])
	{
		printf("%s\n", g_info.env[i]);
		i++;
	}
	return (0);
}

int	execute_unset(char *command)
{
	printf("unsetting %s...\n", command);
	return (0);
}

int	execute_exit(char **commands, int max)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (commands[i] != NULL)
		i++;
	if (max == 1)
		printf("exit\n");
	if (i == 2)
	{
		num = ft_atoi(commands[1]);
		if (ft_isnumber(commands[1]) == 0)
		{
			printf("exit: %s: numeric argument required\n", commands[1]);
			if (max == 1)
				exit(255);
			return (255);
		}
		if (max == 1)
			exit(num % 256);
		return (num % 256);
	}
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	if (max == 1)
		exit(0);
	return (0);
}

int	execute_export(char **commands)
{
	int	i;

	i = 1;
	if (!commands[i])
		execute_env(); // dit moet eigenlijk niet, moet de gesorteerde versie zijn
	while (commands[i])
	{
		if (ft_strchr(commands[i], '='))
		{
			if (!set_env_variable(commands[i]))
				error_exit("Malloc failed", 1);
		}
		i++;
	}
	return (0);
}

int	execute_cd(char *command)
{
	int		ret;
	char	cwd[256];

	ret = 0;
	ret = chdir(command);
	if (ret < 0) //betekent dat map niet bestaat
	{
		printf("%s: no such file or directorrrry\n", command);
		return (1); //exit code!?
	}
	getcwd(cwd, sizeof(cwd));
	set_env_variable(ft_strjoin("PWD=", cwd));
	return (0); //deze 0 wordt later de exit code
}

int	execute_pwd()//char **commands)
{
	// if (execve("/bin/pwd", commands, g_info.env) < 0)
	// 	error_exit("Execve failed", 1);
	printf("%s\n", get_env_variable("PWD"));
	// ook hier goede exit code returnen!!!!!!
	// exit(0);
	return (0);
}


int	execute_echo(char **commands)
{
	//zonder execve schrijven!
	if (execve("/bin/echo", commands, g_info.env) < 0)
		error_exit("Execve failed", 1);
	// printf("executing echo %s...\n", commands[0]);
	return (0);
}

int	find_builtin_function(char **commands, int max)
{
	if (!commands || !commands[0])
		return (-2);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (execute_pwd());
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (execute_cd(commands[1]));
	if (ft_strncmp(commands[0], "export", 7) == 0)
		return (execute_export(commands));
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (execute_unset(commands[1]));
	if (ft_strncmp(commands[0], "env", 4) == 0)
		return (execute_env());
	if (ft_strncmp(commands[0], "exit", 5) == 0)
		return (execute_exit(commands, max));
	return (-1);
}
