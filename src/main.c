/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:52:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 13:53:34 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
//to be replaced by the parser:

char *infiles[3] = {"in1", "in2", "in3"};
char *commands[3] = {"cat", "grep s", "ls"};
char *outfiles[3] = {"out1", "out2", "out3"};

void	print_part(t_part part)
{
	printf("%c %s %s %c %s\n", part.in_r, part.in, part.cmd, part.out_r, part.out);
}

void	print_parts(t_part *parts)
{
	int	i;

	i = 0;
	while (parts[i].cmd)
	{
		print_part(parts[i]);
		i++;
	}
}

t_part	parts_maker(void)
{
	t_part			part;
	int				r;
	unsigned long	i;

	// infile
	r = rand() % 3;
	part.in = malloc((strlen(infiles[r]) + 1) * sizeof(char));
	i = 0;
	while (i < strlen(infiles[r]))
	{
		part.in[i] = infiles[r][i];
		i++;
	}
	part.in[i] = '\0';

	// command
	r = rand() % 3;
	part.cmd = malloc((strlen(commands[r]) + 1) * sizeof(char));
	i = 0;
	while (i < strlen(commands[r]))
	{
		part.cmd[i] = commands[r][i];
		i++;
	}
	part.cmd[i] = '\0';

	// outfile
	r = rand() % 3;
	part.out = malloc((strlen(outfiles[r]) + 1) * sizeof(char));
	i = 0;
	while (i < strlen(outfiles[r]))
	{
		part.out[i] = outfiles[r][i];
		i++;
	}
	part.out[i] = '\0';
	
	//in_r
	r = rand() % 2;
	if (r == 0)
		part.in_r = '<';
	else
		part.in_r = '[';

	//out_r
	r = rand() % 2;
	if (r == 0)
		part.out_r = '>';
	else
		part.out_r = ']';	
	return (part);
}

int	main(int argc, char **argv, char **env)
{
	t_part	*parts;
	int		i;
	int		pipes;

	pipes = 4;
	i = 0;
	argc += 1;
	argv[0] = NULL;
	g_env_variables = env;
	parts = malloc (pipes * sizeof(t_part *));
	while (i < pipes)
	{
		parts[i] = parts_maker();
		print_part(parts[i]);
		i++;
	}
	// executer(0, pipes, -1, parts);
}
