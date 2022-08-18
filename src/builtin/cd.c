/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/17 19:27:44 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief change directory to commands[1]
 * 
 * @param commands 	the directory to change to
 * @param max 		the amount of parts
 * @return int 		0 if cd worked, 1 if it failed
 */
int	execute_cd(char **commands, int max)
{
	int		ret;
	char	cwd[256];
	char	*pwd_str;

	(void)max;
	ret = 0;
	if (!commands[1])
	{
		ft_putstr_fd("mickeyshell: cd: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	ret = chdir(commands[1]);
	if (ret < 0)
		return (error_return(commands[1], 1));
	getcwd(cwd, sizeof(cwd));
	pwd_str = ft_strjoin("PWD=", cwd);
	if (pwd_str == NULL)
		error_exit("malloc failed", 1);
	set_env_variable(pwd_str);
	free(pwd_str);
	return (0);
}
