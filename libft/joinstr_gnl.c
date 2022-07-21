/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   joinstr_gnl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 16:01:22 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 16:01:47 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*joinstr_gnl(char *s1, char c, char *sdef)
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
	sdef[i] = c;
	sdef[i + 1] = '\0';
	return (sdef);
}
