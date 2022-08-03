/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:10:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 19:03:31 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	// remove below
	argc++;
	(void)argv;
	//remove above
	init_global(env);
	printf("%s\n", g_info.paths[0]);
	execute_pwd();
	set_env_variable("PWD=/hoi/dit/is/een/test");
	execute_pwd();
	set_env_variable("PWT=/hoi/dit/is/ook/een/test");
	printf("%s\n", get_env_variable("PWT="));
	return (0);
}
