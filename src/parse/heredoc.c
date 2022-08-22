/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 17:40:33 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief checks for dollar signs in heredoc input and extends the dollar value
 * 
 * @param input 	the string passed in heredoc mode
 * @return char* 	the string from heredoc mode with dollars extended
 */
char	*extend_dollars_hd(char *input)
{
	char	*tmp;

	tmp = ft_strdup(input);
	malloc_check(tmp);
	free(input);
	input = extend_dollars(tmp);
	free (tmp);
	return (input);
}

/**
 * @brief get the word to end the heredoc mode
 * 
 * @param str 		the input on the cmd line
 * @param i 		the current position on the input string of the cmd line
 * @return char* 	the stopping word to end heredoc mode
 */
static char	*get_stop(char *str, int i)
{
	int		j;
	int		len;
	char	*stop;

	j = 0;
	len = calc_len_word_after(str, i);
	stop = malloc((len + 1) * sizeof(char));
	malloc_check(stop);
	while (j < len)
	{
		stop[j] = str[i];
		i++;
		j++;
	}
	stop[j] = '\n';
	stop = remove_quotes(stop);
	return (stop);
}

/**
 * @brief creates the nam for the temp heredoc files, gets the stopping 
 * word for heredoc and calls function to start reading from stdin.
 * 
 * @param str 		the input on the cmd line
 * @param i 		the current position on the input string of the cmd line
 * @param heredocs 	the number of temp heredoc files
 * @return char* 	the name of the temp heredoc file
 */
char	*handle_heredoc(char *str, int i, int heredocs)
{
	char	*stop;
	char	*hd_num;
	char	*hd_filename;

	hd_num = ft_itoa(heredocs);
	malloc_check(hd_num);
	hd_filename = ft_strjoin(".heredoc", hd_num);
	malloc_check(hd_filename);
	stop = get_stop(str, i);
	if (read_from_stdin(stop, hd_filename, heredocs) < 0)
		return (NULL);
	free (stop);
	free (hd_num);
	return (hd_filename);
}
