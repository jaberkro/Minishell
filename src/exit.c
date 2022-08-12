/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:10:32 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/12 15:46:17 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief writes a message to stderr and exits
 * 
 * @param message 	the message to print
 * @param exit_code the code to exit with
 */
void	write_exit(char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	write(STDERR_FILENO, "mickeyshell: ", 13);
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(exit_code);
}

/**
 * @brief writes a message with an argument to stderr, exits
 * 
 * @param argument	the argument to be printed first
 * @param message 	the message to be printed (about the argument)
 * @param exit_code the code to exit with
 */
void	write_exit_argument(char *argument, char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	write(STDERR_FILENO, "mickeyshell: ", 13);
	if (argument)
		write(STDERR_FILENO, argument, ft_strlen(argument));
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(exit_code);
}

/**
 * @brief uses perror to print an error message and exits
 * 
 * @param message 	the message to given to perror
 * @param exit_code the code to exit with
 */
void	error_exit(char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("Malloc failed", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	set_env_variable(return_value);
	free(return_value);
	perror(message);
	exit(exit_code);
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