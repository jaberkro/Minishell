/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:52:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/19 17:52:07 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
//to be replaced by the parser:

t_part	parts_maker(void)
{
	t_part		part;
	int			i;
	static int	j = 0;

	i = 0;
	part.str = malloc(11 * sizeof(char *));
	while (i < 10)
	{
		part.str[i] = i + 65 + j;
		i++;
	}
	part.str[i] = '\0';
	part.lb = '<';
	part.rb = '|';
	j += 10;
	return (part);
}

int	main(int argc, char **argv, char **env)
{
	t_part	*parts;
	int		i;

	i = 0;
	argc += 1;
	argv[0] = NULL;
	g_env_variables = env;
	parts = malloc (4 * sizeof(t_part *));
	while (i < 4)
	{
		parts[i] = parts_maker();
		i++;
	}
	executer(0, 3, -1, parts);
}
