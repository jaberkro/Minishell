/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:28:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 19:16:42 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief copies char **to_copy
 * 
 * @param to_copy 	the char ** to be copied
 * @return char** 	the copy of char **to_copy
 */
char	**copy_array(char **to_copy)
{
	char	**output;
	int		i;

	i = 0;
	if (to_copy == NULL)
		return (NULL);
	while (to_copy[i])
		i++;
	output = malloc((i + 1) * sizeof(char *));
	if (output == NULL)
		error_exit("Malloc failed", 1);
	i = 0;
	while (to_copy[i])
	{
		output[i] = ft_strdup(to_copy[i]);
		if (output[i] == NULL)
			error_exit("Malloc failed", 1);
		i++;
	}
	output[i] = NULL;
	return (output);
}

void	add_variable_to_end(int i, char *variable)
{
	char	**tmp;
	int		j;

	j = 0;
	tmp = copy_array(g_info.env);
	free_array(g_info.env);
	g_info.env = malloc((i + 2) * sizeof(char *));
	if (g_info.env == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	while (j < i)
	{
		g_info.env[j] = ft_strdup(tmp[j]);
		if (g_info.env[j] == NULL)
			error_exit("mickeyshell: malloc failed", 1);
		free(tmp[j]);
		j++;
	}
	g_info.env[j] = ft_strdup(variable);
	if (g_info.env[j] == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	g_info.env[j + 1] = NULL;
	free (tmp);
}

/**
 * @brief Set the env variable object. In case it does not exist yet, it will
 * be added to env. If its exists already it's value will be updated
 * 
 * @param variable 	the env variable to be added to g_info.env
 */
void	set_env_variable(char *variable)
{
	int		i;
	char	*to_find;
	char	*tmp2;

	i = 0;
	to_find = protected_split_grep_one(variable, '=', 0);
	while (g_info.env[i] && \
	!(ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) == 0 && \
	g_info.env[i][ft_strlen(to_find)] == '='))
		i++;
	free(to_find);
	if (!g_info.env[i])
		add_variable_to_end(i, variable);
	else
	{
		tmp2 = ft_strdup(g_info.env[i]);
		if (tmp2 == NULL)
			error_exit("mickeyshell: malloc failed", 1);
		free(g_info.env[i]);
		g_info.env[i] = ft_strdup(variable);
		if (g_info.env[i] == NULL)
			error_exit("mickeyshell: malloc failed", 1);
		free(tmp2);
	}
}
