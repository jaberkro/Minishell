/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   joinstr_gnl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 16:01:22 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/09 10:10:30 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*joinstr_gnl(char *s1, char c, char *sdef)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		sdef[i] = s1[i];
		i++;
	}
	sdef[i] = c;
	sdef[i + 1] = '\0';
	return (sdef);
}
