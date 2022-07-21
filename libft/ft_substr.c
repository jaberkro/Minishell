/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 21:58:16 by bsomers       #+#    #+#                 */
/*   Updated: 2021/09/27 14:31:09 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// On line 29, use strdup because you also need to malloc for empty string
// On line 30, you check if the end of len is after strlen(s)

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			count;
	size_t			strl;

	count = 0;
	if (s == NULL)
		return (0);
	strl = ft_strlen(s);
	if (start >= strl)
		return (ft_strdup(""));
	if ((start + len) > strl)
		len = strl - start;
	sub = malloc((len + 1) * (sizeof(unsigned char)));
	if (sub == NULL)
		return (NULL);
	while (count < len && s[start] != '\0')
	{
		sub[count] = s[start];
		start++;
		count++;
	}
	sub[count] = '\0';
	return (sub);
}
