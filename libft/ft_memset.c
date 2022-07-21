/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:02:18 by bsomers       #+#    #+#                 */
/*   Updated: 2021/03/31 13:59:14 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	ca;

	p = b;
	ca = (unsigned char)c;
	while (len > 0)
	{
		*p = ca;
		p++;
		len--;
	}
	return (b);
}
