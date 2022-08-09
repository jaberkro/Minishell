/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 10:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/09 17:23:54 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

// int	bubble_sort(char **to_sort)
// {
	
// }

// int	print_export(void)
// {
// 	char	**output;

// 	output = bubble_sort(g_info.env);
// }

int	execute_export(char **commands)
{
	int	i;

	i = 1;
	if (!commands[i])
		execute_env(); // dit moet eigenlijk niet, moet de gesorteerde versie zijn
	while (commands[i])
	{
		if (ft_isalpha(commands[i][0]) || (commands[i][0] == '_' && commands[i][1] != '='))
		{
			if (!set_env_variable(commands[i]))
				error_exit("Malloc failed", 1);
		}
		else if ((commands[i][0] != '_'))
		{
			printf("export: `%s': not a valid identifier\n", commands[i]);
		}
		i++;
	}
	return (0);
}
