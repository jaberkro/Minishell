/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 14:31:53 by bsomers       #+#    #+#                 */
/*   Updated: 2021/03/31 14:14:32 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != ('\0'))
	{
		i++;
	}
	while (i > -1)
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}
