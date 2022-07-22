/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/22 15:23:09 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_isred(char c)
{
	if (c == '>' || c == '<')
		return (c);
	return (0);
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
