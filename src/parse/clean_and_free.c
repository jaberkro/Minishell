/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_and_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:21:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 17:13:40 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	delete_temp_heredoc_files(int heredocs)
{
	char	*tmp;
	char	*itoa_hd;

	itoa_hd = NULL;
	tmp = NULL;
	while (heredocs > 0)
	{
		itoa_hd = ft_itoa(heredocs);
		if (itoa_hd == NULL)
			error_exit("malloc", 1);
		tmp = ft_strjoin(".heredoc", itoa_hd);
		if (tmp == NULL)
			error_exit("malloc", 1);
		unlink(tmp);
		free(itoa_hd);
		free(tmp);
		heredocs--;
	}
}

void	free_struct(t_part parts)
{
	free(parts.in);
	free(parts.cmd);
	free(parts.out);
	free(parts.out_r);
}

void	free_struct_split(t_part_split part_split)
{
	if (part_split.in != NULL)
		free_array(part_split.in);
	if (part_split.cmd != NULL)
		free_array(part_split.cmd);
	if (part_split.out != NULL)
		free_array(part_split.out);
	if (part_split.out_r != NULL)
		free(part_split.out_r);
}

void	clean_up(int heredocs, char **input_split, \
t_part_split *part_split, int count)
{
	int	i;

	i = 0;
	free_array(input_split);
	while (i < count)
	{
		free_struct_split(part_split[i]);
		i++;
	}
	free (part_split);
	delete_temp_heredoc_files(heredocs);
}
