/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 11:31:06 by bsomers       #+#    #+#                 */
/*   Updated: 2021/03/31 13:58:14 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		c1;
	const unsigned char	*s1;

	c1 = (unsigned char)c;
	s1 = s;
	i = 0;
	while (i < n)
	{
		if (s1[i] == c1)
			return ((void *)s1 + i);
		i++;
	}
	return (NULL);
}
