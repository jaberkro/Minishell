/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 14:46:35 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 15:35:28 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief increases the value of the SHLVL variable in g_info.env by one
 */
void	increase_shlvl(void)
{
	int		old_level_int;
	char	*old_level_str;
	char	*new_shlvl;
	char	*new_level;

	old_level_str = get_env_variable("SHLVL");
	if (old_level_str == NULL)
		old_level_str = ft_strdup("0");
	old_level_int = ft_atoi(old_level_str);
	free(old_level_str);
	new_level = ft_itoa(old_level_int + 1);
	new_shlvl = ft_strjoin("SHLVL=", new_level);
	free(new_level);
	if (new_shlvl == NULL)
		error_exit("malloc", 1);
	set_env_variable(new_shlvl);
	free(new_shlvl);
}

/**
 * @brief initializes the g_info.env variables
 * 
 * @param env the environment variables given at the start of the program
 */
void	init_env_variables(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	g_info.env = malloc((len + 1) * sizeof(char *));
	if (g_info.env == NULL)
		error_exit("malloc", 1);
	while (i < len)
	{
		g_info.env[i] = ft_strdup(env[i]);
		if (g_info.env[i] == NULL)
			error_exit("malloc", 1);
		i++;
	}
	g_info.env[i] = NULL;
}

/**
 * @brief initializes the global variable
 * 
 * @param env the environment variables given at the start of the program
 */
void	init_global(char **env)
{
	init_env_variables(env);
	g_info.paths = get_paths();
	set_env_variable("?=0");
	increase_shlvl();
	g_info.signal_status = 0;
}
