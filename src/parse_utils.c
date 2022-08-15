/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/15 12:11:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

	j = 0;
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

char	*remove_quotes(char *str)
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
		if (str[i] == 34 || str[i] == 39)
			count_quotes++;
		i++;
	}
	i = 0;
	str_new = malloc((len - count_quotes + 1) * sizeof(char));
	str_new = strdup_no_quotes(str, str_new, i, len);
	return (str_new);
}

int	set_quote_flag(int q, char c)
{
	if ((c == 34 || c == 39) && q == 0)
		q = 1;
	else if ((c == 34 || c == 39) && q == 1)
		q = 0;
	return (q);
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

void	free_struct(t_part parts)
{
	free(parts.in);
	free(parts.cmd);
	free(parts.out);
	free(parts.out_r);
	//free(parts);
}

void	free_struct_split(t_part_split part_split)
{
	if (part_split.in != NULL)
		free_array(part_split.in);
	if (part_split.cmd != NULL)
		free_array(part_split.cmd);
	if (part_split.out != NULL)
		free_array(part_split.out);
	if (part_split.out_r != NULL)
		free(part_split.out_r);
}
