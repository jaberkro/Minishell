/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 10:17:48 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/20 15:33:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

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
	return (sdef);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

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

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc((sizeof(char)) *(len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
