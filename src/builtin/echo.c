/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:58 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 15:33:10 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	execute_echo(char **commands)
{
	int	i;

	i = 1;
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
