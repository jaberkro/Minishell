/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 18:23:28 by jaberkro      ########   odam.nl         */
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
 * @brief checks if a char is a double quote: "
 * 
 * @param c 	the char to check
 * @return int 	1 if it is indeed a double quote, 0 if it is not
 */
int	double_quote(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

char	*add_dollar(char *input)
{
	char	*to_add;

	to_add = ft_strdup("$");
	if (to_add == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	input = ft_strjoin_fr(input, to_add);
	if (input == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	free(to_add);
	return (input);
}

/**
 * @brief copies input between start_index and i to the end of output
 * 
 * @param input 	the string to copy from
 * @param i 		the index of the '$' sign
 * @param output 	the output so far, where the extended var gets added to
 * @return char* 	the old output with the extended variable added to it
 */
char	*add_extended_variable(char *input, int *i, char *output, int d_quote)
{
	char	*to_join;
	char	*to_find;
	int		end;

	end = 1;
	if (ft_isspace(input[*i + end]))
	{
		printf("only one dollar!\n");
		to_join = ft_strdup("$");
		if (to_join == NULL)
			error_exit("mickeyshell: malloc failed", 1);
	}
	else
	{
		printf("something behind the dollar!\n");
		if (!(d_quote == 0 && double_quote(input[*i + end])))
		{
			while (input[*i + end] != '\0' && !ft_isspace(input[*i + end]) && \
			input[*i + end] != '$' && ft_isred(input[*i + end]) == 0 && \
			!single_quote(input[*i + end]) && ((!double_quote(input[*i + end]) && d_quote == 0) || (double_quote(input[*i + end]) && d_quote == 0))) // dit moet nog anders
				end++;
		}
		printf("len to_find:[%d]\n", end);
		to_find = ft_substr(input, (unsigned int)(*i) + 1, end - 1);
		if (to_find == NULL)
			error_exit("mickeyshell: malloc failed", 1);
		to_find = remove_double_quotes(to_find);
		to_join = get_env_variable(to_find);
		if (to_join == NULL && output == NULL)
			return (ft_strdup(""));
		free(to_find);
	}
	if (output == NULL)
		output = ft_strdup(to_join);
	else if (to_join != NULL)
		output = ft_strjoin_fr(output, to_join);
	if (output == NULL)
		error_exit("mickeyshell: malloc failed", 1);
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
		error_exit("mickeyshell: malloc failed", 1);
	if (output == NULL)
		output = ft_strdup(to_join);
	else
		output = ft_strjoin_fr(output, to_join);
	if (output == NULL)
		error_exit("mickeyshell: malloc failed", 1);
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
	int		s_quote;
	int		d_quote;
	char	*output;

	i = 0;
	start = 0;
	s_quote = 0;
	d_quote = 0;
	output = NULL;
	while (input[i] != '\0')
	{
		if (single_quote(input[i]))
			s_quote = !s_quote;
		else if (double_quote(input[i]))
			d_quote = !d_quote;
		else if (s_quote == 0 && input[i] == '$' && \
		input[i + 1] != '\0' /*&& !ft_isspace(input[i + 1])*/ && \
		!(d_quote == 1 && double_quote(input[i + 1])))
		{
			if (input[start] != '$')
				output = add_normal_text(input, &start, i, output);
			output = add_extended_variable(input, &i, output, d_quote);
			// printf("i now:[%d]\n", i);
			// printf("out:[%s]\n", output);
			start = i;
		}
		// else if (s_quote == 0 && ft_isspace(input[i + 1]))
		// {
		// 	output = add_dollar(output);
		// 	i++;
		// }
		if (input[i] != '\0')
			i++;
	}
	output = add_normal_text(input, &start, i - start, output);
	printf("out:[%s]\n", output);
	return (output);
}
