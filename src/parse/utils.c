/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 16:25:34 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// #include <stdio.h>

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
			return (write_return("wrong use of pipes\n", -1));
		if (str[i] == '|' && q == 0)
			j++;
		i++;
	}
	if ((i - quotes) == j || q != 0)
		return (write_return("wrong use of quotes and/or pipes\n", -1));
	return (j);
}

void	malloc_check(char *str)
{
	if (str == NULL)
		error_exit("malloc", 1);
}

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
