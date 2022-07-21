/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 17:17:44 by bsomers       #+#    #+#                 */
/*   Updated: 2021/09/26 12:33:50 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Line 24 looks for length of dst without null (that fits within size)

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	i;

	len_dest = 0;
	i = 0;
	while (len_dest < size && dst[len_dest] != '\0')
		len_dest++;
	while (len_dest + i + 1 < size && src[i] != '\0')
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	if (len_dest + i < size)
		dst[len_dest + i] = '\0';
	return (len_dest + ft_strlen(src));
}
