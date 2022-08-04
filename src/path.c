/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 13:04:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/04 17:37:47 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*make_path(char *path)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(path);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	tmp = command;
	command = ft_strjoin(command, "/");
	free(tmp);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	return (command);
}

char	*command_in_paths(char	*argument, char **paths)
{
	int		i;
	char	*command;
	char	*tmp;

	i = 0;
	// printf("argument: [%s]\n", argument);
	if (access(argument, X_OK) != -1)
		return (argument);
	if (!paths)
		write_exit_argument(argument, ": No such file or directory\n", 127);
	while (paths && paths[i])
	{
		command = make_path(paths[i]);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("Malloc failed", 1);
		if (access(command, X_OK) != -1)
			return (command);
		free(command); // is this necessary?
		i++;
	}
	write_exit_argument(argument, ": command not found\n", 127);
	return (NULL);
}

char	**get_paths(void)
{
	int		i;
	char	**splitted_paths;
	char	*paths;

	i = 0;
	paths = get_env_variable("PATH");
	if (!paths)
		return (NULL);
	splitted_paths = protected_split(paths, ':');
	return (splitted_paths);
}
