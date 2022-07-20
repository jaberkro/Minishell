/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 16:11:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/19 18:38:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		counter++;
		s++;
	}
	return (counter);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*out;	

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	out = malloc(len + 1);
	if (out == NULL)
		return (NULL);
	while (*s1)
	{
		*out = *s1;
		out++;
		s1++;
	}
	while (*s2)
	{
		*out = *s2;
		out++;
		s2++;
	}
	*out = '\0';
	return (out - len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	len;

	counter = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (counter < dstsize - 1 && src[counter])
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (dstsize != 0)
		dst[counter] = '\0';
	return (len);
}

void	*ft_memset(void	*b, int c, size_t len)
{
	size_t	counter;

	counter = 0;
	while (counter < len)
	{
		((unsigned char *)b)[counter] = (unsigned char)c;
		counter++;
	}
	return ((void *)(b));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*out;

	out = malloc(count * size);
	if (out == NULL)
		return (NULL);
	ft_memset(out, 0, size * count);
	return (out);
}
