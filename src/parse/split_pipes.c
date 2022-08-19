/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/28 17:05:37 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 16:57:19 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	wcount(char const *s, char c)
{
	int	i;
	int	d;
	int	w;
	int	q;

	d = 0;
	w = 0;
	q = 0;
	i = ft_strlen(s);
	while (d < i)
	{
		q = set_quote_flag(q, s[d]);
		if (q == 0)
		{
			if (d > 0)
				if (s[d] != c && ((s[d - 1] == c && (s[d] != 34 && s[d] != 39)) \
				|| (d - 1) == -1))
					w++;
			if (d < 1)
				if (s[d] != c)
					w++;
		}
		d++;
	}
	return (w + 1);
}

static void	check_quotes(char *s1, int *w_ptr, int *q_ptr, char c)
{
	int	w;
	int	q;

	w = *w_ptr;
	q = *q_ptr;
	while (s1[w] != '\0')
	{
		q = set_quote_flag(q, s1[w]);
		if (s1[w] == c && q == 0)
			break ;
		w++;
	}
	*q_ptr = q;
	*w_ptr = w;
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
	check_quotes(s1, &w, &q, c);
	word = ft_calloc(w + 1, sizeof(char));
	if (word == NULL)
		error_exit("malloc", 1);
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
		error_exit("malloc", 1);
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
