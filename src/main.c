/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:52:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 18:36:46 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//to be replaced by the parser:

// char infiles[3][10] = {"in1\0", "in2\0", "in3\0"};
// char commands[3][10] = {"cat\0", "grep s\0", "ls\0"};
// char outfiles[3][10] = {"out1\0", "out2\0", "out3\0"};

void	print_part(t_part part)
{
	if (part.in_r)
	{
		write(1, &part.in_r, 1);
		write(1, " ", 1);
		write(1, part.in, ft_strlen(part.in) + 1);
		write(1, " ", 1);
	}
	write(1, part.cmd, ft_strlen(part.cmd));
	if (part.out_r == '>' || part.out_r == ']')
	{
		write(1, " ", 1);
		write(1, &part.out_r, 1);
		write(1, " ", 1);
		write(1, part.out, ft_strlen(part.out) + 1);
	}
	write(1, "\n", 1);
	// printf("%c %s %s %c %s\n", part.in_r, part.in, part.cmd, part.out_r, part.out);
}

void	print_parts(t_part *parts, int pipes)
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		print_part(parts[i]);
		i++;
	}
}

t_part	part_maker(int i, int max)
{
	t_part			part;
	unsigned long	r;

	ft_bzero(&part.in, 1);
	ft_bzero(&part.cmd, 1);
	ft_bzero(&part.out, 1);
	part.in_r = '\0';
	part.out_r = '\0';

	
	// command
	r = rand() % 3;
	if (r == 0)
		part.cmd = ft_strdup("cat");
	else if (r == 1)
		part.cmd = ft_strdup("ls");
	else 
		part.cmd = ft_strdup("grep e");
	// printf("cmd: |%s|\n", part.cmd);

	//in_r
	if (i == 0 || i == max % 4)
	{
		// infile
		r = rand() % 3;
		if (r == 0)
			part.in = ft_strdup("in1");
		else if (r == 1)
			part.in = ft_strdup("in2");
		else if (r == 2)
			part.in = ft_strdup("in3");
		part.in_r = '<';
	// 	// printf("in: |%s|\n", part.in);
	}

	// //out_r
	if (i == max - 1 || i == max % 5)
	{
		//outfile
		r = rand() % 6;
		if (r == 0)
			part.out = ft_strdup("out1");
		else if (r == 1)
			part.out = ft_strdup("out2");
		else if (r == 2)
			part.out = ft_strdup("out3");
		else if (r == 3)
			part.out = ft_strdup("out4");
		else if (r == 4)
			part.out = ft_strdup("out5");
		else if (r == 5)
			part.out = ft_strdup("out6");
		// printf("out: |%s|\n", part.out);
		part.out_r = '>';
	}
	return (part);
}

int	main()
{
	t_part	*parts;
	int		i;
	int		pipes;
	int		pid;
	int		status;

	pipes = 7;
	i = 0;
	parts = malloc ((pipes + 1) * sizeof(t_part));
	while (i < pipes)
	{
		parts[i] = part_maker(i, pipes);
		i++;
	}
	ft_bzero(&parts[i].in, 1);
	ft_bzero(&parts[i].cmd, 1);
	ft_bzero(&parts[i].out, 1);
	parts[i].in_r = '\0';
	parts[i].out_r = '\0';
	printf("_____________________________\n");
	print_parts(parts, pipes);
	printf("_____________________________\n");
	pid = executer(0, pipes, -1, parts);
	waitpid(pid, &status, 0);
	exit(WEXITSTATUS(status));

}
