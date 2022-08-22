/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_and_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:21:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 17:02:31 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief deletes the temporary files used for the heredoc
 * 
 * @param heredocs the number of temp heredoc files
 */
void	delete_temp_heredoc_files(int heredocs)
{
	char	*tmp;
	char	*itoa_hd;

	itoa_hd = NULL;
	tmp = NULL;
	while (heredocs > 0)
	{
		itoa_hd = ft_itoa(heredocs);
		malloc_check(itoa_hd);
		tmp = ft_strjoin(".heredoc", itoa_hd);
		malloc_check(tmp);
		unlink(tmp);
		free(itoa_hd);
		free(tmp);
		heredocs--;
	}
}

/**
 * @brief frees parts of the struct used in the parser
 * 
 * @param parts the struct used in the parser
 */
void	free_struct(t_part parts)
{
	free(parts.in);
	free(parts.cmd);
	free(parts.out);
	free(parts.out_r);
}

/**
 * @brief frees the parts of the split struct used in the parser
 * 
 * @param part_split the split struct used in the parser
 */
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

/**
 * @brief frees used struct arrays and deletes temp heredoc files
 */
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
