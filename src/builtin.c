/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/11 10:35:38 by jaberkro      ########   odam.nl         */
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
		if (ft_strncmp(g_info.env[i], "?=", 2) != 0 && \
		ft_strchr(g_info.env[i], '='))
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

void	execute_exit(char **commands, int max)
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
			exit(255);
		}
		exit(num % 256);
	}
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	exit(0);
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

int	execute_pwd(void) //char **commands)
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
	int	i;

	i = 1;
	// set_env_variable("?=0");
	if (!commands[i])
	{
		printf("\n");
		return (0);
	}
	while (commands[i])
	{
		if (i != 1 || (i == 1 && ft_strncmp(commands[1], "-n", 3) != 0))
		{
			if ((i != 1 && ft_strncmp(commands[1], "-n", 3) != 0))
				printf(" ");
			printf("%s", commands[i]);
		}
		i++;
	}
	if (ft_strncmp(commands[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}

int	find_builtin_function(char **commands, int max)
{
	int		status;
	char	*status_num;

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
		error_exit("Malloc failed", 1);
	if (status != -1)
		set_env_variable(ft_strjoin("?=", status_num));
	free(status_num);
	return (status);
}
