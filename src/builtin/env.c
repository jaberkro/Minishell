/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:29:01 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/16 15:01:07 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief prints all env variables that have an '=' sign in them except _=
 * 
 * @param commands 	not needed, here because of jumptable
 * @param max 		not needed, here because of jumptable
 * @return int 		returnvalue to exit with
 */
int	execute_env(char **commands, int max)
{
	int	i;

	i = 0;
	(void)max;
	(void)commands;
	while (g_info.env[i])
	{
		if (ft_strncmp(g_info.env[i], "?=", 2) != 0 && \
		ft_strchr(g_info.env[i], '='))
		{
			ft_putendl_fd(g_info.env[i], STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
