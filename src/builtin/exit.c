/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:36 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 15:42:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	execute_exit(char **commands, int max)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (commands[i] != NULL)
		i++;
	if (max == 1)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (i == 2)
	{
		num = ft_atoi(commands[1]);
		if (ft_isnumber(commands[1]) == 0)
		{
			ft_putstr_fd("mickeyshell: exit: ", STDOUT_FILENO);
			ft_putstr_fd(commands[1], STDOUT_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
			exit(255);
		}
		exit(num % 256);
	}
	if (i > 2)
		write_exit("exit: too many arguments\n", 1);
	exit(0);
}
