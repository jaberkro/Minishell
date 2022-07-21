/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr_gnl.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 16:00:06 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 16:16:50 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char const *s, unsigned int st, size_t len, t_gnl *stat)
{
	char			*sub;
	size_t			count;
	size_t			strl;

	count = 0;
	if (s == NULL)
		return (0);
	strl = ft_strlen(s);
	if (strl == 0)
		return (NULL);
	if ((st + len) > strl)
		len = strl - st;
	sub = malloc((len + 1) * (sizeof(unsigned char)));
	if (sub == NULL)
		stat->flag = 1;
	if (stat->flag == 1)
		return (NULL);
	while (count < len && s[st] != '\0')
	{
		sub[count] = s[st];
		st++;
		count++;
	}
	sub[count] = '\0';
	return (sub);
}
