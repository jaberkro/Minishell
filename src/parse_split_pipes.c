/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_pipes.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/28 17:05:37 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/28 17:24:55 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h> //weeeeegggg!!!

static int	wcount(char const *s, char c)
{
	int	i;
	int	d;
	int	w;
    int q;

	d = 0;
	w = 0;
    q = 0;
	i = ft_strlen(s);
	while (d < i)
	{
        if ((s[d] == 34 || s[d] == 39) && q == 0)
            q = 1;
		else if ((s[d] == 34 || s[d] == 39) && q == 1)
			q = 0;
		if (q == 0)
		{
			if (d > 0)
				if (s[d] != c && ((s[d - 1] == c && (s[d] != 34 && s[d] != 39)) || (d - 1) == -1))
					w++;
			if (d < 1)
				if (s[d] != c)
					w++;
		}
		// printf("S[d]: %c, d: %d, q: %d, w: %d\n", s[d], d, q, w);
		d++;
	}
	// printf("Chunks to split to: %d\n", w);
	return (w + 1);
}

static char	*wsplit(const char **s, char c)
{
	int		w;
	int		x;
	int		q;
	char	*s1;
	char	*word;

	s1 = (char *)*s;
	w = 0;
	x = 0;
	q = 0;
	while (s1[w] != '\0')// && s1[w] != c)
	{
		// printf("s1[w]: %c, w: %d, q: %d\n", s1[w], w, q);
		if ((s1[w] == 34 || s1[w] == 39) && q == 0)
			q = 1;
		else if ((s1[w] == 34 || s1[w] == 39) && q == 1)
			q = 0;
		if (s1[w] == c && q == 0)
			break;
		w++;
	}
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
	while (*s1 != '\0' && *s1 == c && q == 0)
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

char	**ft_split_pipes(char const *s, char c)
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
		// printf("Chunk made: -%s-\n", array[x]);
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
