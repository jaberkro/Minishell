/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 13:09:51 by bsomers       #+#    #+#                 */
/*   Updated: 2021/09/26 12:21:33 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wcount(char const *s, char c)
{
	int	i;
	int	d;
	int	w;

	d = 0;
	w = 0;
	i = ft_strlen(s);
	while (d < i)
	{
		if (d > 0)
			if (s[d] != c && (s[d - 1] == c || (d - 1) == -1))
				w++;
		if (d < 1)
			if (s[d] != c)
				w++;
		d++;
	}
	return (w + 1);
}

static char	*wsplit(const char **s, char c)
{
	int		w;
	int		x;
	char	*s1;
	char	*word;

	s1 = (char *)*s;
	w = 0;
	x = 0;
	while (s1[w] != '\0' && s1[w] != c)
		w++;
	word = ft_calloc(w + 1, sizeof(char));
	if (word == NULL)
		return (NULL);
	while (x < w)
	{
		word[x] = *s1;
		s1++;
		x++;
	}
	word[x] = '\0';
	while (*s1 != '\0' && *s1 == c)
		s1++;
	*s = s1;
	return (word);
}

static char	**clearspace(char **array, int x)
{
	while (x > 0)
	{
		x--;
		free(array[x]);
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		x;
	int		w;

	if (s == NULL)
		return (NULL);
	while (*s == c && *s != '\0')
		s++;
	x = 0;
	w = wcount(s, c);
	array = ft_calloc(w + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (w > x && *s != '\0')
	{
		array[x] = wsplit(&s, c);
		if (array[x] == NULL)
		{
			clearspace(array, x);
			return (NULL);
		}
		x++;
	}
	array[x] = NULL;
	return (array);
}
