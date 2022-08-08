/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:04:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/08 14:33:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	execute_exit(char **commands)
{
	printf("exiting... with code [%s]\n", commands[1]);
	return (0);
}

int	execute_env(void)
{
	int	i;

	i = 0;
	while (g_info.env[i])
	{
		printf("%s\n", g_info.env[i]);
		i++;
	}
	return(0);
}

int	execute_unset(char *command)
{
	printf("unsetting %s...\n", command);
	// exit(0);

	return (0);
}

int	execute_exit(char **commands)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	//printf("commands[2] = %s\n", commands[2]);
	while (commands[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		return (1);//Hiet foutmelding invoegen, exitcode 1, want too many args!
	}
	if (i > 1)
	{
		num = ft_atoi(commands[1]);
		printf("commands[1] = %s\n", commands[1]);
		if (ft_isnumber(commands[1]) == 0)
		{
			ft_printf("exit: %s: numeric argument required\n", commands[1]);
			return (255);//Hier foutmelding (exitcode 255) invoegen, want het is geen nummer! maar hij exit wel!
		}
	}
	// if ( > 256)
	// 	num = num - //Hier goede berekening nvoeren bij te hoog exit nummer!
	return (num % 256);
}

int	execute_export(char **commands)
{
	int	i;

	i = 1;
	if (!commands[i])
		execute_env(); // dit moet eigenlijk niet, meot de gesorteerde versie zijn
	//zonder argumenten de gesorteerde versie printen
	while (commands[i])
	{
		if (ft_strchr(commands[i], '='))
		{
			printf("exporting %s...\n", commands[i]);
			if (!set_env_variable(commands[i]))
				printf("exporting %s failed\n", commands[i]);
		}
		i++;
	}
	return (0);
}

int	execute_cd(char *command)
{
	int	ret;
	printf("changing to directory %s...\n", command);
	if (access(command, F_OK) == 0)
		ret = chdir(command);
	else
		ret = chdir(ft_strjoin(get_env_variable("PWD"), command));
	if (ret < 0) //betekent dat map niet bestaat
	{
		printf("%s: no such file or directorrrry\n", command);
		//goed returnen!
	}
	//en ook de env variables in global updaten!
	// exit(0);
	return (0); //deze 0 wordt later de exit code
}

int	execute_pwd()//char **commands)
{
	// if (execve("/bin/pwd", commands, g_info.env) < 0)
	// 	error_exit("Execve failed", 1);
	printf("DEZE: %s\n", get_env_variable("PWD"));
	// ook hier goede exit code returnen!
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

int	find_builtin_function(char **commands)
{
	if (!commands || !commands[0])
		return (-2); // geen commando aanwezig
	// if (ft_strncmp(commands[0], "echo", 5) == 0)
	// 	return (execute_echo(commands));
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
		return (execute_exit(commands));
	return (-1);
}
