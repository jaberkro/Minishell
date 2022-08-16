/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/16 16:52:19 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	ft_isemptyline(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strncmp(str, "", 1) == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) != 0)
			j++;
		i++;
	}
	if (j == i)
		return (0);
	return (1);
}

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

int	is_double_red(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_isred(str[i]) != 0)
		{
			while (ft_isred(str[i]) != 0)
			{
				i++;
				j++;
			}
			if ((j == 2 && str[0] == '<' && str[1] == '>') || (j == 3 && \
			(str[i - j + 1] == '<')) || (j == 3 && (str[i - j + 1] == '>')))
				return (-1);
			else if ((j > 3 && (str[i - j + 1] == '>')) || \
			(j > 3 && (str[i - j + 1] == '<')))
				return (-1);
			else
				j = 0;
		}
		i++;
	}
	return (0);
}

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
		if (str[i] == '|' && str[i + 1] == '|' && q == 0)
		{
			printf("mickeyshell: wrong use of pipes\n");
			return (-1);
		}
		if (str[i] == '|' && q == 0)
			j++;
		i++;
	}
	if ((i - quotes) == j || q != 0)
	{
		printf("mickeyshell: wrong use of quotes and/or pipes\n");
		return (-1);
	}
	return (j);
}
