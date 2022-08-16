/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:58 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/16 14:58:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	if (ft_strncmp(commands[1], "-n", 3) == 0)
		i++;
	while (commands[i])
	{
		ft_putstr_fd(commands[i], STDOUT_FILENO);
		if (commands[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (ft_strncmp(commands[1], "-n", 3) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
