/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 18:27:09 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief 		calculates the length of the following word in the string
 * 
 * @param str 	the string to get the word from
 * @param i 	the current position on the string
 * @return int 	the lenght of the following word
 */
int	calc_len_word_after(char *str, int i)
{
	int	count;

	count = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0)
	{
		i++;
		count++;
	}
	return (count);
}

/**
 * @brief sets a part of str to spaces
 * 
 * @param str 		the string that (partially) needs to be set to spaces
 * @param start 	the starting position of the part that needs to be set to spaces
 * @param len 		the number of characters that need to be set to spaces
 * @return char* 	the string with the replaced characters
 */
char	*set_space(char *str, int start, int len)
{
	int	i;

	i = start;
	while (i < (len + start))
	{
		str[i] = ' ';
		i++;
	}
	return (str);
}

/**
 * @brief 		checks if a pipe is used wrong in a string
 * 
 * @param str 	the string to check
 * @param i 	the current index of the position on the string
 * @param q 	the quote flag
 * @return int 	0 if the usage is wrong, 1 if the usage is OK
 */
int	check_pipe(char *str, int i, int q)
{
	if ((str[i] == '|' && str[i + 1] == '|' && q == 0) || (str[i] == '|' && \
		str[i + 1] == '\0'))
		return (0);
	else if (str[i] == '|')
	{
		i++;
		while (ft_isspace(str[i]) != 0)
			i++;
		if (str[i] == '|')
			return (0);
	}
	return (1);
}

/**
 * @brief 		counts the number of pipes and checks for wrong quotes usage
 * 
 * @param str 	the string to check and count on
 * @return int 	the number of pipes, -1 in case of wrong use of pipes/quotes
 */
int	count_pipes(char *str)
{
	int	i;
	int	j;
	int	q;
	int	quotes;

	i = 0;
	j = 0;
	q = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39 || str[i] == 34)
		{
			q = set_quote_flag(q, str[i]);
			quotes++;
		}
		if (check_pipe(str, i, q) == 0)
			return (write_return("wrong use of pipes\n", -1));
		if (str[i] == '|' && q == 0)
			j++;
		i++;
	}
	if ((i - quotes) == j || q != 0)
		return (write_return("wrong use of quotes and/or pipes\n", -1));
	return (j);
}

/**
 * @brief sets the part in the array of structs to zero
 * 
 * @param part 			the array of structs with non-split strings
 * @param part_split 	the array of structs with splitted strings
 */
void	set_zero_parts(t_part *part, t_part_split *part_split)
{
	part->in = NULL;
	part->out = NULL;
	part->cmd = NULL;
	part->out_r = NULL;
	part_split->in = NULL;
	part_split->out = NULL;
	part_split->cmd = NULL;
	part_split->out_r = NULL;
}
