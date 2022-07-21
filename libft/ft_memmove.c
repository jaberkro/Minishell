/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 19:53:48 by bsomers       #+#    #+#                 */
/*   Updated: 2021/03/31 14:09:35 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_overlap(const void *dst, const void *src, size_t len)
{
	if (src < dst && dst < src + len)
		return (1);
	else
		return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (((void *)dst == NULL) && ((void *)src == NULL))
		return (NULL);
	if (ft_overlap(dst, src, len))
	{
		while (i < len)
		{
			x = len - i - 1;
			((unsigned char *)dst)[x] = ((unsigned char *)src)[x];
			i++;
		}
		return (dst);
	}
	else
	{
		while (i < len)
		{
			i++;
			((unsigned char *)dst)[i - 1] = ((const unsigned char *)src)[i - 1];
		}
	}
	return (dst);
}
