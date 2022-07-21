/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 11:52:06 by bsomers       #+#    #+#                 */
/*   Updated: 2021/09/26 12:29:59 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n == -2147483648)
	{
		n = n + 2000000000;
		len = len + 1;
	}
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*calc_a(char *str, int n, int i)
{
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = n + 2000000000;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		len_n;

	len_n = calc_len(n);
	i = len_n - 1;
	str = malloc((sizeof(char)) * (len_n + 1));
	if (str == NULL)
		return ((char *) NULL);
	str[len_n] = '\0';
	str = calc_a(str, n, i);
	return (str);
}
