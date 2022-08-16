/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 20:24:19 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief removes all commands from the env list except commands[0]
 * 
 * @param commands 
 * @param max 
 * @return int 
 */
int	execute_unset(char **commands, int max)
{
	int	i;

	i = 1;
	(void)max;
	while (commands[i])
	{
		unset_env_variable(commands[i]);
		i++;
	}
	return (0);
}
