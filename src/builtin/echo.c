/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:58 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/18 13:04:16 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief checks if string is option n.
 * 
 * @param command 	the command to check
 * @return int  	-n returns 1, -nnnnnn returns 1, otherwise return 0
 */
int	is_option_n(char *command)
{
	int	i;

	i = 0;
	if (command[i] == '-')
		i++;
	else
		return (0);
	while (command[i] == 'n')
		i++;
	if (command[i] != '\0')
		return (0);
	return (1);
}

/**
 * @brief executes the echo command. Prints all commands with a space inbetween.
 * Ends with a newline unless commands[1] is -n 
 * 
 * @param commands	the commands to be printed. commands[0] is echo and will not
 * be printed. If commands[1] is -n, it will not be printed and there won't be
 * a newline in the end.
 * @param max 		the amount of parts
 * @return int 		the exit code of echo
 */
int	execute_echo(char **commands, int max)
{
	int	i;

	i = 1;
	(void)max;
	if (!commands[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	while (commands[i] && is_option_n(commands[i]))
		i++;
	while (commands[i])
	{
		ft_putstr_fd(commands[i], STDOUT_FILENO);
		if (commands[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (commands[1] && is_option_n(commands[1]) == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
