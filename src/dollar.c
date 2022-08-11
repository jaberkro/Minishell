/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/11 13:52:46 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief checks if a char is a single quote: '
 * 
 * @param c 	the char to check
 * @return int 	1 if it is indeed a single quote, 0 if it is not
 */
int	single_quote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

/**
 * @brief copies input between start_index and i to the end of output
 * 
 * @param input 	the string to copy from
 * @param i 		the index of the '$' sign
 * @param output 	the output so far, where the extended var gets added to
 * @return char* 	the old output with the extended variable added to it
 */
char	*add_extended_variable(char *input, int *i, char *output)
{
	char	*to_join;
	char	*to_find;
	int		end;

	end = 1;
	while (input[*i + end] != '\0' && !ft_isspace(input[*i + end]) && \
	input[*i + end] != '$' && ft_isred(input[*i + end]) == 0)
		end++;
	to_find = ft_substr(input, (unsigned int)(*i) + 1, end - 1);
	if (to_find == NULL)
		error_exit("Malloc failed", 1);
	to_join = get_env_variable(to_find);
	free(to_find);
	// if (output == NULL)
	// 	output = ft_strdup(to_join);
	// else
		output = ft_strjoin_fr(output, to_join);
	free (to_join);
	*i += end;
	return (output);
}

/**
 * @brief copies input from start to i to the end of output
 * 
 * @param input 	the input to copy from
 * @param start 	the start index
 * @param i 		the end index
 * @param output 	the output before the input gets copied
 * @return char* 	output and new text from input combined
 */
char	*add_normal_text(char *input, int *start, int i, char *output)
{
	char	*to_join;

	to_join = ft_substr(input, *start, i);
	if (to_join == NULL)
		error_exit("Malloc failed", 1);
	if (output == NULL)
		output = ft_strdup(to_join);
	else
		output = ft_strjoin_fr(output, to_join);
	if (output == NULL)
		error_exit("Malloc failed", 1);
	free(to_join);
	return (output);
}

/**
 * @brief extends all dollars in the input sentence
 * 
 * @param input		the input to be extended
 * @return char* 	the extended input
 */
char	*extend_dollars(char *input)
{
	int		i;
	int		start;
	int		quote;
	char	*output;

	i = 0;
	start = 0;
	quote = 0;
	output = NULL;
	while (input[i] != '\0')
	{
		if (single_quote(input[i]))
			quote = !quote;
		else if (quote == 0 && input[i] == '$' && \
		input[i + 1] != '\0' && !ft_isspace(input[i + 1]))
		{
			output = add_normal_text(input, &start, i, output);
			output = add_extended_variable(input, &i, output);
			start = i;
		}
		if (input[i] != '\0')
			i++;
	}
	output = add_normal_text(input, &start, i - start, output);
	return (output);
}
