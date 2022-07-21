/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 18:47:30 by bsomers       #+#    #+#                 */
/*   Updated: 2021/03/31 13:59:48 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	int		i;
	int		all;

	all = nmemb * size;
	ptr = malloc(all);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (all > i)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
