/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 16:11:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 16:31:20 by jaberkro      ########   odam.nl         */
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

char	*ft_strdup(const char *s1)
{
	char	*out;
	int		len;

	len = ft_strlen(s1);
	out = malloc(len + 1);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, s1, len + 1);
	return (out);
}

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, '\0', n);
}

// int	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == -2147483648)
// 		ft_putstr_fd("-2147483648", fd);
// 	else if (n == 0)
// 		return (ft_putchar_fd('0', fd));
// 	else if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		ft_putnbr_fd(-n, fd);
// 	}
// 	else if (n > 9)
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putchar_fd((n % 10) + 48, fd);
// 	}
// 	else if (n >= 0)
// 		ft_putchar_fd((n % 10) + 48, fd);
// 	return (ft_intlen(n));
// }