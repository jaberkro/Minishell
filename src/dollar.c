/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/04 17:33:01 by jaberkro      ########   odam.nl         */
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
	// printf("input:[%s]\n", input);
	while (input[i] != '\0')
	{
		if (input[i] == 39 && quote == 0)
			quote = 1;
		else if (input[i] == 39)
			quote = 0;
		else if (input[i] == '$' && quote == 0 && input[i + 1] != '\0' && !ft_isspace(input[i + 1]))
		{
			// printf("$ found at index %d, copying from index %d\n", i, last_end);
			tmp = ft_substr(input, last_end, i - last_end);
			// printf("tmp: [%s]\n", tmp);
			if (tmp)
				output = ft_strjoin(output, tmp);
			// printf("output so far:[%s]\n", output);
			env_len = 1;
			while (input[i + env_len] != '\0' && !ft_isspace(input[i + env_len]) && input[i + env_len] != '$' && ft_isred(input[i + env_len]) == 0)
			{
				env_len++;
			}
			// printf("i: %d env_len: %d\n", i, env_len - 1);
			tmp2 = get_env_variable(ft_substr(input, i + 1, env_len - 1));
			// printf("tmp2: [%s] gives [%s]\n", ft_substr(input, i + 1, env_len - 1), tmp2);
			if (tmp2)
				output = ft_strjoin(output, tmp2);
			// printf("output so far:[%s]\n", output);
			i += env_len;
			last_end = i;
		}
		if (input[i] != '\0')
			i++;
	}
	// printf("end at index %d, copying from index %d\n", i, last_end);
	tmp = ft_substr(input, last_end, i - last_end);
	// printf("tmp: [%s]\n", tmp);
	if (tmp)
		output = ft_strjoin(output, tmp);
	// printf("output so far:[%s]\n", output);
	return (output);
}
