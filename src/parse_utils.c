/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/04 15:01:38 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	ft_isred(char c)
{
	if (c == '>' || c == '<')
		return (c);
	return (0);
}

char	*remove_quotes(char *str)
{
	int	len;
	char	*str_new;
	int	count_quotes;
	int	i;
	int j;

	i = 0;
	j = 0;
	count_quotes = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == 34 || str[i] == 39)
			count_quotes++;
		i++;
	}
	i = 0;
	str_new = malloc((len - count_quotes + 1) * sizeof(char));
	while (i < len)
	{
		if (str[i] != 34 && str[i] != 39)
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
