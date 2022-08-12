/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/12 16:57:16 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	execute_unset(char *command)
{
	printf("unsetting %s...\n", command);
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
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (ft_strncmp(commands[1], "-n", 3) == 0)
		i++;
	while (commands[i])
	{
		write(STDOUT_FILENO, commands[i], ft_strlen(commands[i]));
		if (commands[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (ft_strncmp(commands[1], "-n", 3) != 0)
		write(STDOUT_FILENO, "\n", 1);
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
