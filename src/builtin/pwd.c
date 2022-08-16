/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 18:33:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //weghalen

int	execute_pwd(char **commands, int max)
{
	(void)max;
	(void)commands;
	// if (execve("/bin/pwd", commands, g_info.env) < 0)
	// 	error_exit("Execve failed", 1);
	printf("%s\n", get_env_variable("PWD"));
	// ook hier goede exit code returnen!!!!!!
	// exit(0);
	return (0);
}