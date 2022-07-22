/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_ftsplit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 18:34:05 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 16:51:56 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	**free_all(char **out, int wcounter)
{
	int	counter;

	counter = 0;
	while (counter < wcounter)
	{
		free(out[counter]);
		counter++;
	}
	free(out);
	return (NULL);
}

static char	**out_filler(char const *s, char c, char **out)
{
	int	wcounter;
	int	last;
	int	wordlen;

	last = 0;
	wcounter = 0;
	while (*s != '\0')
	{
		if (*s != c && *s)
		{
			wordlen = 0;
			while (s[wordlen] != c && s[wordlen] != '\0')
				wordlen++;
			out[wcounter] = malloc(wordlen + 1);
			if (out[wcounter] == NULL)
				return (free_all(out, wcounter));
			ft_strlcpy(out[wcounter], s, wordlen + 1);
			wcounter++;
			s += wordlen;
			if (!*s)
				break ;
		}
		s++;
	}
	return (out);
}

static int	count_words(char const *s, char c)
{
	int	words;
	int	last;

	words = 0;
	last = 0;
	while (*s)
	{
		if (*s != c && last == 0)
		{
			last = 1;
			words++;
		}
		if (*s == c)
			last = 0;
		s++;
	}
	// printf("words: %d\n", words);
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**out;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	out = ft_calloc(words + 1, sizeof(char *));
	if (out == NULL)
		return (NULL);
	return (out_filler(s, c, out));
}