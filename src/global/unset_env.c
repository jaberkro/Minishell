/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 19:17:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/16 15:10:41 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief copies array tmp into g_info.env but skips tmp[to_unset]
 * 
 * @param to_unset 	the index not to copy
 * @param tmp 		the array to copy
 */
void	remove_variable_from_env(int to_unset, char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i] && i < to_unset)
	{
		g_info.env[i] = ft_strdup(tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	while (tmp[i + 1])
	{
		g_info.env[i] = ft_strdup(tmp[i + 1]);
		free(tmp[i + 1]);
		i++;
	}
	g_info.env[i] = NULL;
	free(tmp);
}

/**
 * @brief Unset the env variable object. In case it does not exist yet, it will
 * be added to env. If its exists already it's value will be updated
 * 
 * @param variable 	the env variable to be added to g_info.env
 */
void	unset_env_variable(char *variable)
{
	int		i;
	char	*to_find;
	char	**tmp;
	int		len;

	i = 0;
	len = 0;
	to_find = protected_split_grep_one(variable, '=', 0);
	while (g_info.env[i] && \
	!(ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) == 0 && \
	(g_info.env[i][ft_strlen(to_find)] == '=' || \
	g_info.env[i][ft_strlen(to_find)] == '\0')))
		i++;
	free(to_find);
	if (g_info.env[i])
	{
		tmp = copy_array(g_info.env);
		free_array(g_info.env);
		while (tmp[len])
			len++;
		g_info.env = malloc(len * sizeof(char *));
		if (g_info.env == NULL)
			error_exit("malloc failed", 1);
		remove_variable_from_env(i, tmp);
	}
}
