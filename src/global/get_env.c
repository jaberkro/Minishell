/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 19:15:13 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 17:04:33 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Get the env variable object
 * 
 * @param to_find 	the key of the variable to find
 * @return char* 	the value behind the '=' sign
 */
char	*get_env_variable(char *to_find)
{
	int		i;
	char	*output;

	i = 0;
	while (g_info.env[i] && \
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0)
		i++;
	if (!g_info.env[i])
		return (NULL);
	if (g_info.env[i][ft_strlen(to_find)] == '=')
	{
		output = ft_strdup(g_info.env[i] + ft_strlen(to_find) + 1);
		if (output == NULL)
			error_exit("malloc", 1);
		return (output);
	}
	return (NULL);
}
