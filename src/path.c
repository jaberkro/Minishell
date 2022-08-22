/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 13:04:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 17:51:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief takes a path and uses ft_strjoin to glue a '/' to the end.
 * 
 * @param path 		the path that will get a '/' behind it
 * @return char* 	the new path with a '/' behind it
 */
static char	*make_path(char *path)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(path);
	if (command == NULL)
		error_exit("malloc", 1);
	tmp = command;
	command = ft_strjoin(command, "/");
	free(tmp);
	if (command == NULL)
		error_exit("malloc", 1);
	return (command);
}

/**
 * @brief checks if a command is found by joining it with one of the paths
 * 
 * @param argument 	the command to find in the system functions
 * @param paths 	the paths to all system functions
 * @return char* 	the path to the command is the command is found, else NULL
 */
char	*command_in_paths(char	*argument, char **paths)
{
	int		i;
	char	*command;

	i = 0;
	if (access(argument, X_OK) != -1)
		return (argument);
	if (!paths)
		write_exit_argument(argument, ": No such file or directory\n", 127);
	if (!argument)
		exit(0);
	while (paths && paths[i])
	{
		command = make_path(paths[i]);
		command = ft_strjoin_fr(command, argument);
		if (command == NULL)
			error_exit("malloc", 1);
		if (access(command, X_OK) != -1)
			return (command);
		free(command);
		i++;
	}
	write_exit_argument(argument, ": command not found\n", 127);
	return (NULL);
}

/**
 * @brief Get the paths from the global env variable
 * 
 * @return char** 	the paths, splitted on ':'
 */
char	**get_paths(void)
{
	char	**splitted_paths;
	char	*paths;

	paths = get_env_variable("PATH");
	if (!paths)
		return (NULL);
	splitted_paths = protected_split(paths, ':');
	free(paths);
	return (splitted_paths);
}
