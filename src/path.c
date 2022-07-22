/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 13:04:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 13:15:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

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
	if (access(argument, X_OK) != -1)
		return (argument);
	if (!paths)
		write_exit_argument(argument, ": No such file or directory\n", 127);
	if (!argument)
		write_exit(": command not found\n", 127);
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
