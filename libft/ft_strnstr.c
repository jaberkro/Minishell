/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 14:40:50 by bsomers       #+#    #+#                 */
/*   Updated: 2021/04/07 14:56:34 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strnstr locates the first occurrence of the null-
// terminated string needle in the string haystack, where not more 
// than len characters are searched.  Characters that appear 
// after a `\0' character are not searched.

// If needle is an empty string, haystack is returned.
// If needle occurs nowhere in haystack, NULL is returned. 
// Otherwise a pointer to the first character of the first 
// occurrence of needle is returned.

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)hay);
	while (i <= len || hay[i] == '\0')
	{
		if (hay[i] == needle[0])
		{
			j = 0;
			while (hay[i + j] == needle[j] && ((i + j) < len))
			{
				j++;
				if (needle[j] == '\0')
					return (&((char *)hay)[i]);
			}
			if (j == ft_strlen(needle))
				return (&((char *)hay)[i]);
		}
		i++;
	}
	return (NULL);
}
