/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_and_finish.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:20:37 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/18 11:04:47 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/wait.h>

void	if_exited(int status)
{
	char	*itoa_exit;
	char	*return_value;

	itoa_exit = ft_itoa(WEXITSTATUS(status));
	if (itoa_exit == NULL)
		error_exit("malloc failed", 1);
	return_value = ft_strjoin("?=", itoa_exit);
	if (return_value == NULL)
		error_exit("malloc failed", 1);
	free(itoa_exit);
	set_env_variable(return_value);
	free(return_value);
}

void	call_executer(int count_pipe, t_part_split *part_split)
{
	int	pid;
	int	fd;
	int	i;
	int	status;
	// struct sigaction	sa;

	// sa.sa_handler = &sig_handler;
	fd = dup(0);
	i = 1;
	pid = executer(0, count_pipe + 1, fd, part_split);
	// sigaction(SIGINT, &sa, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		if_exited(status);
	while (i < count_pipe + 1)
	{
		wait(NULL);
		i++;
	}
	close (fd);
}

void	exec_minishell(char *input)
{
	char			**input_split;
	t_part_split	*part_split;
	int				count_pipe;
	int				heredocs;

	heredocs = 0;
	input_split = ft_split_pipes(input, '|');
	count_pipe = count_pipes(input);
	if (input_split == NULL)
		error_exit("malloc failed", 1);
	if (count_pipe < 0)
	{
		free_array(input_split);
		return ;
	}
	part_split = malloc((count_pipe + 2) * sizeof(t_part_split));
	if (part_split == NULL)
		error_exit("malloc failed", 1);
	ft_bzero(&part_split[count_pipe + 1], sizeof(t_part_split));
	heredocs = set_fill_split_parts(input_split, count_pipe, \
	part_split, heredocs);
	if (heredocs < 0)
		return ;
	call_executer(count_pipe, part_split);
	clean_up(heredocs, input_split, part_split, count_pipe + 2);
}
