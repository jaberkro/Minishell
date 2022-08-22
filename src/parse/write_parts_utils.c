/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_parts_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 15:50:06 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 18:07:36 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief sets the corresponding string in an array to the name of
 * the filename mentioned in the str from the cmd line. 
 * 
 * @param to_set 	the string in the array to set
 * @param str 		the original cmd line
 * @param start 	the starting position of the filename
 * @param len 		the length of the filename
 * @return char* 	the string with only the filename
 */
char	*assign_filename(char *to_set, char *str, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	malloc_check(tmp);
	tmp = ft_strtrim_fr(tmp, " ");
	malloc_check(tmp);
	if (to_set == NULL)
		to_set = ft_strdup(tmp);
	else
	{
		to_set = ft_strjoin_fr(to_set, " ");
		malloc_check(to_set);
		to_set = ft_strjoin_fr(to_set, tmp);
		malloc_check(to_set);
	}
	free(tmp);
	return (to_set);
}

/**
 * @brief sets the corresponding string in an array to the redirector
 * mentioned in the str from the cmd line. 
 * 
 * @param str 		the str in the parts struct that needs to be set
 * @param red 		the found redirector
 * @return char* 	the set str in the parts struct
 */
char	*assign_redirector(char *str, char *red)
{
	if (str == NULL)
		str = ft_strdup(red);
	else
		str = ft_strjoin_fr(str, red);
	malloc_check(str);
	return (str);
}

/**
 * @brief 		loops over a string to the end of a word while taking 
 * into account possible quotes
 * 
 * @param i_ptr the pointer to the index of the string
 * @param q_ptr the pointer to the quote flag
 * @param str 	the string to loop over
 */
void	loop_to_end_word(int *i_ptr, int *q_ptr, char *str)
{
	int	i;
	int	q;

	i = *i_ptr;
	q = *q_ptr;
	while (((q == 0) && (ft_isspace(str[i]) == 0) && (ft_isred(str[i]) == 0) && \
	(str[i] != '\0')) || ((q != 0) && str[i] != '\0'))
	{
		q = set_quote_flag(q, str[i]);
		i++;
	}
	*i_ptr = i;
	*q_ptr = q;
}
