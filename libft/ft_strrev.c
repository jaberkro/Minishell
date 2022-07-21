/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:39:23 by bsomers       #+#    #+#                 */
/*   Updated: 2022/01/25 18:58:11 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *rev)
{
	int		len;
	char	temp;
	int		i;

	len = ft_strlen(rev);
	i = 0;
	while (i < (len / 2 + 1))
	{
		temp = rev[i];
		rev[i] = rev[len - i - 1];
		rev[len - i - 1] = temp;
		i++;
	}
	return (rev);
}
