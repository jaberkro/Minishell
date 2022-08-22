/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:21:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 16:44:58 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

static void	loop_until_red(int *i_ptr, int *j_ptr, char *str)
{
	int	i;
	int	j;

	i = *i_ptr;
	j = *j_ptr;
	while (ft_isred(str[i]) != 0)
	{
		i++;
		j++;
	}
	*i_ptr = i;
	*j_ptr = j;
}

static int	isred_with_space(char *str, int i)
{
	if (ft_isspace(str[i + 1]) != 0)
		i++;
	while (ft_isspace(str[i]) != 0)
		i++;
	if (ft_isred(str[i]) != 0)
		return (-1);
	return (0);
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
			loop_until_red(&i, &j, str);
			if ((j == 2 && str[0] == '<' && str[1] == '>') || (j == 3 && \
			(str[i - j + 1] == '<')) || (j == 3 && (str[i - j + 1] == '>')) || \
			(j == 2 && (str[i - j + 1] != str[i - j])))
				return (-1);
			else if ((j > 3 && (str[i - j + 1] == '>')) || \
			(j > 3 && (str[i - j + 1] == '<')))
				return (-1);
			else if (isred_with_space(str, i) != 0)
				return (-1);
			else
				j = 0;
		}
		i++;
	}
	return (0);
}
