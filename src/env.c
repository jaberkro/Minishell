/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:28:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/10 15:26:57 by bsomers       ########   odam.nl         */
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

/**
 * @brief Get the env variable object
 * 
 * @param to_find 	the key of the variable to find
 * @return char* 	the value behind the '=' sign
 */
char	*get_env_variable(char *to_find)
{
	int	i;

	i = 0;
	while (g_info.env[i] && \
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0)
		i++;
	if (!g_info.env[i])
		return (NULL);
	if (g_info.env[i][ft_strlen(to_find)] == '=')
		return (g_info.env[i] + ft_strlen(to_find) + 1);
	return (NULL);
}

/**
 * @brief Set the env variable object
 * 
 * @param variable 	the env variable to be added to g_info.env
 * @return int 		return 1 if it worked // not needed to catch this anymore
 */
int	set_env_variable(char *variable)
{
	int		i;
	char	*to_find;
	char	**tmp;
	char	*tmp2;
	int		j;

	i = 0;
	j = 0;
	to_find = ft_split(variable, '=')[0]; //BS: We moeten dit anders inregelen, want 
										//de resterende strings in deze array kunnen we zo niet freeen!
	if (to_find == NULL)
		error_exit("Malloc failed", 1);
	while (g_info.env[i] && \
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0) // and check for enter in correct space
		i++;
	free(to_find);
	if (!g_info.env[i])
	{
		tmp = copy_array(g_info.env);
		free_array(g_info.env);
		g_info.env = malloc((i + 2) * sizeof(char *));
		if (g_info.env == NULL)
			error_exit("Malloc failed", 1);
		while (j < i)
		{
			g_info.env[j] = ft_strdup(tmp[j]);
			if (g_info.env[j] == NULL)
				error_exit("Malloc failed", 1);
			free(tmp[j]);
			j++;
		}
		g_info.env[j] = ft_strdup(variable);
		if (g_info.env[j] == NULL)
			error_exit("Malloc failed", 1);
		g_info.env[j + 1] = NULL;
		free (tmp);
	}
	else
	{
		tmp2 = ft_strdup(g_info.env[i]);
		if (g_info.env[j] == NULL)
			error_exit("Malloc failed", 1);
		free (g_info.env[i]);
		g_info.env[i] = ft_strdup(variable);
		if (g_info.env[i] == NULL)
			error_exit("Malloc failed", 1);
		free(tmp2);
	}
	//free (variable); //BS toegevoegd op 10/8 15:00, maar soms is voor variable niet altijd gemallocd dus weer weg
	return (1);
}
