/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   global.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 12:54:31 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 13:17:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = protected_split(env[i] + 5, ':');
	return (paths);
}

void	create_global(char **env)
{
	g_info.env = env;
	g_info.paths = get_paths(env);
}
