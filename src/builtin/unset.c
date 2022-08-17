/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/17 15:06:32 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
		if (ft_strncmp(commands[i], "PATH", 5) == 0 && g_info.paths)
		{
			free_array(g_info.paths);
			g_info.paths = NULL;
		}
		i++;
	}
	return (0);
}
