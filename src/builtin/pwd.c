/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/16 14:59:00 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	execute_pwd(char **commands, int max)
{
	char	cwd[256];

	(void)max;
	(void)commands;
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
