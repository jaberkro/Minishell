/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/10 18:16:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

char	*extend_dollars(char *input)
{
	int		i;
	int		env_len;
	int		last_end;
	int		quote;
	char	*output;
	char	*tmp;
	char	*tmp2;

	i = 0;
	quote = 0;
	tmp = NULL;
	tmp2 = NULL;
	output = ft_strdup("");
	last_end = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 39 && quote == 0)
			quote = 1;
		else if (input[i] == 39)
			quote = 0;
		else if (input[i] == '$' && quote == 0 && input[i + 1] != '\0' && !ft_isspace(input[i + 1]))
		{
			tmp = ft_substr(input, last_end, i - last_end);
			if (tmp)
				output = ft_strjoin_fr(output, tmp);
			env_len = 1;
			while (input[i + env_len] != '\0' && !ft_isspace(input[i + env_len]) && input[i + env_len] != '$' && ft_isred(input[i + env_len]) == 0)
			{
				env_len++;
			}
			tmp2 = get_env_variable(ft_substr(input, i + 1, env_len - 1));
			if (tmp2)
			{
				output = ft_strjoin_fr(output, tmp2);
				free (tmp2);
			}
			i += env_len;
			last_end = i;
		}
		if (input[i] != '\0')
			i++;
	}
	tmp = ft_substr(input, last_end, i - last_end); //malloc protect
	if (tmp)
	{
		output = ft_strjoin_fr(output, tmp);
		free (tmp);
	}
	free (input); //toegevoegd tijdens leaks check 10-8
	return (output);
}

//Notitie van Britt: soms ft_strjoin vervangen door ft_strjoin_fr, want die free'd
//de eerste variable die naar strjoin wordt gestuurd