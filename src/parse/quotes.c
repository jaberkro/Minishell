/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:23:06 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 17:30:53 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Set the quote flag for the corresponding quote
 * 
 * @param q 	the flag to indicate the quote situation
 * @param c 	the char to check which quote is present
 * @return int 	0 for no quote, 1 for single quote, 2 for double quote
 */
int	set_quote_flag(int q, char c)
{
	if ((c == 34) && q == 2)
		q = 0;
	else if ((c == 34) && q == 0)
		q = 2;
	else if ((c == 39) && q == 0)
		q = 1;
	else if (c == 39 && q == 1)
		q = 0;
	return (q);
}

/**
 * @brief copies string str to str_new without double quotes
 * 
 * @param str 		the original string from which double quotes should be removed
 * @param str_new 	the new string without double quotes
 * @param i 		the index on the original string
 * @param len 		the length of the original string
 * @return char* 	the new string without double quotes
 */
static char	*strdup_no_double_quotes(char *str, char *str_new, int i, int len)
{
	int	j;

	j = 0;
	while (i < len)
	{
		if (str[i] != 34)
		{
			str_new[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	str_new[j] = '\0';
	free(str);
	return (str_new);
}

/**
 * @brief counts double quotes, mallocs for new string and calls function to delete double quotes from string
 * 
 * @param str 		the string from which double quotes need to be removed
 * @return char* 	the new string from which double quotes have been removed
 */
char	*remove_double_quotes(char *str)
{
	int		len;
	char	*str_new;
	int		count_quotes;
	int		i;

	i = 0;
	count_quotes = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == 34)
			count_quotes++;
		i++;
	}
	i = 0;
	str_new = malloc((len - count_quotes + 1) * sizeof(char));
	malloc_check(str_new);
	str_new = strdup_no_double_quotes(str, str_new, i, len);
	return (str_new);
}

/**
 * @brief copies string str to str_new without quotes
 * 
 * @param str 		the original string from which quotes should be removed
 * @param str_new 	the new string without quotes
 * @param i 		the index on the original string
 * @param len 		the length of the original string
 * @return char* 	the new string without quotes
 */
static char	*strdup_no_quotes(char *str, char *str_new, int i, int len)
{
	int	j;
	int	q;

	j = 0;
	q = 0;
	while (i < len)
	{
		if ((((str[i] == 34 || str[i] == 39) && q == 0)) || \
		((str[i] == 34) && q == 2) || ((str[i] == 39) && q == 1))
		{
			q = set_quote_flag(q, str[i]);
			i++;
		}
		else
		{
			str_new[j] = str[i];
			j++;
			i++;
		}
	}
	str_new[j] = '\0';
	free(str);
	return (str_new);
}

/**
 * @brief counts any quotes, mallocs for new string and calls function to delete  quotes from string
 * 
 * @param str 		the string from which quotes need to be removed
 * @return char* 	the new string from which quotes have been removed
 */
char	*remove_quotes(char *str)
{
	int		len;
	char	*str_new;
	int		count_quotes;
	int		i;
	int		q;

	i = 0;
	q = 0;
	count_quotes = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (((str[i] == 34 || str[i] == 39) && q == 0) || \
		((str[i] == 34) && q == 2) || ((str[i] == 39) && q == 1))
		{
			q = set_quote_flag(q, str[i]);
			count_quotes++;
		}
		i++;
	}
	i = 0;
	str_new = malloc((len - count_quotes + 1) * sizeof(char));
	malloc_check(str_new);
	str_new = strdup_no_quotes(str, str_new, i, len);
	return (str_new);
}
