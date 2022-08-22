/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 17:04:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief extends a variable
 * 
 * @param i 		the index of the input we want to extend
 * @param len 		the length of the word to be extended
 * @param input 	the input that we want to extend 
 * @return char* 	the extended variable
 */
char	*extend_variable(int i, int *len, char *input)
{
	char	*to_find;
	char	*to_join;

	while (input[i + *len] != '\0' && !ft_isspace(input[i + *len]) && \
		input[i + *len] != '$' && ft_isred(input[i + *len]) == 0 && \
		input[i + *len] != 39 && input[i + *len] != 34)
			(*len)++;
	to_find = ft_substr(input, (unsigned int)(i) + 1, *len - 1);
	if (to_find == NULL)
		error_exit("malloc", 1);
	to_find = remove_double_quotes(to_find);
	to_join = get_env_variable(to_find);
	if (to_join == NULL)
		to_join = ft_strdup("");
	free(to_find);
	return (to_join);
}

/**
 * @brief copies input between start_index and i to the end of output
 * 
 * @param input 	the string to copy from
 * @param i 		the index of the '$' sign
 * @param output 	the output so far, where the extended var gets added to
 * @return char* 	the old output with the extended variable added to it
 */
char	*add_extended_variable(char *input, int *i, char *output, int quotes)
{
	char	*to_join;
	int		len;

	len = 1;
	if (ft_isspace(input[*i + 1]))
		to_join = ft_strdup("$");
	else if (quotes != 2 && input[*i + 1] == 34)
		to_join = ft_strdup("");
	else
		to_join = extend_variable(*i, &len, input);
	if (to_join == NULL)
		error_exit("malloc", 1);
	if (output == NULL)
		output = ft_strdup(to_join);
	else
		output = ft_strjoin_fr(output, to_join);
	if (output == NULL)
		error_exit("malloc", 1);
	free (to_join);
	*i += len;
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
		error_exit("malloc", 1);
	if (output == NULL)
		output = ft_strdup(to_join);
	else
		output = ft_strjoin_fr(output, to_join);
	if (output == NULL)
		error_exit("malloc", 1);
	free(to_join);
	return (output);
}

/**
 * @brief updates quotes. quotes is either 0 (no quotes), 1 (single quote) or
 * 2 (double quote). If quotes is 0, any quote can be set. If it's 1, quotes
 * can only be updated with the occurrence of a single quote. If it's 2, 
 * quotes can only be updated with the occurrence of a double quote
 * 
 * @param c 		the current char to check
 * @param quotes 	0, 1 or 2 dependent on if we encountered no quotes, a 
 * single quote or double quotes before encountering this char c
 * @return int 		0, 1 or 2 dependent on the updated state of quotes
 */
int	update_quotes(char c, int quotes)
{
	if (c == 39 && quotes != 2)
		quotes = !quotes;
	else if (c == 34 && quotes != 1)
		quotes = !quotes * 2;
	return (quotes);
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
	int		quotes;
	char	*output;

	i = 0;
	start = 0;
	quotes = 0;
	output = NULL;
	while (input[i] != '\0')
	{
		quotes = update_quotes(input[i], quotes);
		if (quotes != 1 && input[i] == '$' && input[i + 1] != '\0' && \
		!(quotes == 2 && input[i + 1] == 34))
		{
			if (input[start] != '$')
				output = add_normal_text(input, &start, i, output);
			output = add_extended_variable(input, &i, output, quotes);
			start = i;
		}
		if (input[i] != '\0')
			i++;
	}
	output = add_normal_text(input, &start, i - start, output);
	return (output);
}
