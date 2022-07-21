/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 13:40:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/04/20 15:32:58 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (str[i] == '\0' && (str[i - 1] == '-' || str[i - 1] == '+'))
		return (0);
	return (1);
}
