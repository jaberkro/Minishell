/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/12 14:08:43 by jaberkro      ########   odam.nl         */
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
		{
			write(STDOUT_FILENO, g_info.env[i], ft_strlen(g_info.env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
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
		write(STDOUT_FILENO, "exit\n", 5);
	if (i == 2)
	{
		num = ft_atoi(commands[1]);
		if (ft_isnumber(commands[1]) == 0)
		{
			write(STDERR_FILENO, "mickeyshell: exit: ", 19);
			write(STDERR_FILENO, commands[1], ft_strlen(commands[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit(255);
		}
		exit(num % 256);
	}
	if (i > 2)
		write_exit("exit: too many arguments\n", 1);
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
	if (!commands[i])
	{
		printf("\n");//write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (ft_strncmp(commands[1], "-n", 3) == 0)
		i++;
	while (commands[i])
	{
		printf("%s", commands[i]); //write(STDOUT_FILENO, commands[i], ft_strlen(commands[i]));
		if (commands[i + 1])
			printf(" "); //write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (ft_strncmp(commands[1], "-n", 3) != 0)
		printf("\n");//write(STDOUT_FILENO, "\n", 1);
	return (0);
}

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
		error_exit("Malloc failed", 1);
	if (status != -1)
	{
		status_str = ft_strjoin("?=", status_num);
		set_env_variable(status_str);
		free(status_str);
	}
	free(status_num);
	return (status);
}
