/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   global.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 12:54:31 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/05 17:26:22 by bsomers       ########   odam.nl         */
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
	if (g_info.env[i][ft_strlen(to_find)] == '=')
		return (g_info.env[i] + ft_strlen(to_find) + 1);
	else
		return (NULL);
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
	ft_strncmp(g_info.env[i], to_find, ft_strlen(to_find)) != 0) // and check for enter in correct space
		i++;
	if (!g_info.env[i])
	{
		tmp = g_info.env;
		g_info.env = malloc((i + 2) * sizeof(char *));
		if (g_info.env == NULL)
			return (0);
		while (j < i)
		{
			g_info.env[j] = tmp[j];
			j++;
		}
		g_info.env[j] = variable;
		g_info.env[j + 1] = NULL;
		free (tmp);
	}
	else
	{
		g_info.env[i] = variable;
	}
	return (1);
}

int	increase_shlvl(void)
{
	int		old_shlvl;
	char	*new_shlvl;

	old_shlvl = ft_atoi(get_env_variable("SHLVL"));
	new_shlvl = ft_strjoin("SHLVL=", ft_itoa(old_shlvl + 1));
	if (new_shlvl == NULL)
		return (0);
	if (!set_env_variable(new_shlvl))
		return (0);
	return (1);
}

int	init_env_variables(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	g_info.env = malloc((len + 1) * sizeof(char *));
	if (g_info.env == NULL)
		return (0);
	while (i < len)
	{
		g_info.env[i] = env[i];
		i++;
	}
	g_info.env[i] = NULL;
	return (1);
}

void	init_global(char **env)
{
	if (!init_env_variables(env))
		error_exit("Malloc failed", 1);
	g_info.paths = get_paths();
	if (!set_env_variable("?=0"))
		error_exit("Malloc failed", 1);
	if (!increase_shlvl())
		error_exit("Malloc failed", 1);
}
