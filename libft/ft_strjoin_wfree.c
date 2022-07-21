/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_wfree.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 12:47:37 by bsomers       #+#    #+#                 */
/*   Updated: 2022/06/10 13:22:47 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*joinstr(char *s1, char *s2, char *sdef)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		sdef[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		sdef[i] = s2[j];
		i++;
		j++;
	}
	sdef[i] = '\0';
	free(s1);
	return (sdef);
}

char	*ft_strjoin_fr(char const *s1, char const *s2)
{
	char	*sdef;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	sdef = malloc((i + j + 1) * (sizeof(unsigned char)));
	if (sdef == NULL)
		return (NULL);
	sdef = joinstr((char *)s1, (char *)s2, sdef);
	return (sdef);
}
