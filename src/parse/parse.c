/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 18:06:38 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

/**
 * @brief calls functions to extend dollars and remove excessive quotes
 * 
 * @param array 	the array with strings to loop over
 * @return char** 	the original array but with extended dollars and removed 
 * quotes
 */
char	**extend_dollars_remove_quotes(char **array)
{
	int		i;
	char	*tmp;

	i = 0;
	while (array && array[i] != NULL)
	{
		tmp = array[i];
		array[i] = extend_dollars(tmp);
		free(tmp);
		array[i] = remove_quotes(array[i]);
		i++;
	}
	return (array);
}

/**
 * @brief splits strings in original array of structs into double arrays in 
 * new split structs, extends dollars and removes excessive quotes.
 * 
 * @param part 			original struct
 * @param part_split 	new struct where words are split into double arrays
 */
void	split_parts(t_part *part, t_part_split *part_split)
{
	if (part->out_r != NULL)
		part_split->out_r = ft_strdup(part->out_r);
	if (part->out != NULL)
		part_split->out = ft_split_pipes(part->out, ' ');
	if (part->cmd != NULL)
		part_split->cmd = ft_split_pipes(part->cmd, ' ');
	if (part->in != NULL)
		part_split->in = ft_split_pipes(part->in, ' ');
	part_split->out = extend_dollars_remove_quotes(part_split->out);
	part_split->cmd = extend_dollars_remove_quotes(part_split->cmd);
	part_split->in = extend_dollars_remove_quotes(part_split->in);
}

/**
 * @brief checks which redirector is found and calls corresponding function
 * 
 * @param part 	struct with strings to assign to
 * @param str 	user input string from cmd line
 * @param q_ptr pointer to flag that shows if you're reading in between quotes
 * @param i_ptr pointer to index on str
 * @return char* user input string from cmd line without word assigned
 */
char	*select_red(t_part *part, char *str, int *q_ptr, int *i_ptr)
{
	int	i;
	int	q;

	i = *i_ptr;
	q = *q_ptr;
	if (str[i] == '>' && str[i + 1] != '>')
		str = to_outfile(part, str, &q, &i);
	else if (str[i] == '>' && str[i + 1] == '>')
		str = to_outfile_app(part, str, &q, &i);
	else if (str[i] == '<' && str[i + 1] != '<')
		str = from_infile(part, str, &q, &i);
	*i_ptr = i;
	*q_ptr = q;
	return (str);
}

/**
 * @brief loops through string from cmd line, checks for redirectors and 
 * then assigns the filenames and cmds to corresponding parts in the structs
 * 
 * @param part 		struct with strings to assign to
 * @param str 		user input string from cmd line
 * @param heredocs 	number of temp heredoc documents
 * @return int 		number of temp heredoc documents
 */
int	assign_parts(t_part *part, char *str, int heredocs)
{
	int	i;
	int	q;
	int	hd_flag;

	i = 0;
	q = 0;
	hd_flag = 0;
	while (i < ((int)ft_strlen(str)))
	{
		q = set_quote_flag(q, str[i]);
		if ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '>' && \
		str[i + 1] == '>') || (str[i] == '<' && str[i + 1] != '<'))
			str = select_red(part, str, &q, &i);
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			heredocs++;
			str = from_heredoc(part, str, heredocs, &i);
			if (str == NULL)
				return (-1);
		}
		else
			i++;
	}
	part->cmd = ft_strdup(str);
	return (heredocs);
}

/**
 * @brief makes struct with parts and assigns with corresponding word 
 * from cmd line input.
 * 
 */
int	set_fill_split_parts(char **input_split, int count_pipe, \
t_part_split *part_split, int heredocs)
{
	int		i;
	t_part	*parts;

	i = 0;
	parts = malloc((count_pipe + 1) * sizeof(t_part));
	if (parts == NULL)
		error_exit("malloc", 1);
	while (i < (count_pipe + 1))
	{
		set_zero_parts(&parts[i], &part_split[i]);
		heredocs = assign_parts(&parts[i], input_split[i], heredocs);
		if (heredocs < 0)
			return (-1);
		split_parts(&parts[i], &part_split[i]);
		free_struct(parts[i]);
		i++;
	}
	free(parts);
	return (heredocs);
}
