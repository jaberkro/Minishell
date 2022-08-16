/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:23:06 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/16 16:57:38 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	str_new = strdup_no_double_quotes(str, str_new, i, len);
	return (str_new);
}

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
	str_new = strdup_no_quotes(str, str_new, i, len);
	return (str_new);
}
