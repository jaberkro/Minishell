/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 18:34:21 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h> //weghalen

int	execute_cd(char **commands, int max)
{
	int		ret;
	char	cwd[256];

	(void)max;
	ret = 0;
	ret = chdir(commands[1]);
	if (ret < 0) //betekent dat map niet bestaat
	{
		printf("%s: no such file or directorrrry\n", commands[1]);
		return (1); //exit code!?
	}
	getcwd(cwd, sizeof(cwd));
	set_env_variable(ft_strjoin("PWD=", cwd));
	return (0); //deze 0 wordt later de exit code
}
