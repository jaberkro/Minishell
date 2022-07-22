/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   global.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 12:54:31 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 15:25:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

char	*get_env_variable(char *to_find)
{
	int	i;

	i = 0;
	while (g_info.env[i] && \
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0)
		i++;
	if (!g_info.env[i])
		return (NULL);
	return (g_info.env[i] + ft_strlen(to_find));
}

int	set_env_variable(char *variable)
{
	int		i;
	char	*to_find;
	char	**tmp;
	int		j;

	i = 0;
	j = 0;
	to_find = ft_split(variable, '=')[0];
	if (to_find == NULL)
		return (0);
	while (g_info.env[i] && \
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0)
		i++;
	if (!g_info.env[i])
	{
		tmp = g_info.env;
		g_info.env = malloc((i + 1) * sizeof(char *));
		if (g_info.env == NULL)
			return (0);
		while (j < i)
		{
			g_info.env[j] = tmp[j];
			j++;
		}
		g_info.env[j] = variable;
		g_info.env[j + 1] = NULL;
	}
	else
	{
		g_info.env[i] = variable;
	}
	return (1);
}

void	init_global(char **env)
{
	g_info.env = env;
	g_info.paths = get_paths();
}
