/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_wfree.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:46:35 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/10 14:13:04 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*copy_set(char *sdef, char *s1, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		sdef[i] = s1[start];
		i++;
		start++;
	}
	sdef[i] = '\0';
	free (s1);
	return (sdef);
}

char	*ft_strtrim_fr(char const *s1, char const *set)
{
	char	*sdef;
	size_t	start;
	size_t	end;

	if (set == NULL || s1 == NULL)
		return ((char *) s1);
	start = 0;
	while (s1[start] && check_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], set))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	sdef = malloc((sizeof(char)) * (end - start + 1));
	if (sdef == NULL)
		return (NULL);
	copy_set(sdef, (char *)s1, start, end);
	return (sdef);
}
