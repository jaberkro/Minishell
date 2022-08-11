/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 10:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/11 17:34:16 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	is_sorted(char **to_check)
{
	int		i;
	int		j;

	i = 0;
	while (to_check[i] && to_check[i + 1])
	{
		j = 0;
		while (to_check[i][j] && to_check[i + 1][j] && \
		to_check[i][j] == to_check[i + 1][j])
			j++;
		if (to_check[i][j] > to_check[i + 1][j])
			return (0);
		i++;
	}
	return (1);
}

char	**bubble_sort(char **to_sort)
{
	char	*tmp;
	int		i;
	int		j;

	if (to_sort == NULL) // is dit nodig??? Zal iemand alle env variabelen unsetten?
		return (NULL);
	while (!is_sorted(to_sort))
	{
		i = 0;
		while (to_sort[i] && to_sort[i + 1])
		{
			j = 0;
			while (to_sort[i][j] == to_sort[i + 1][j])
				j++;
			if (to_sort[i][j] > to_sort[i + 1][j])
			{
				tmp = to_sort[i];
				to_sort[i] = to_sort[i + 1];
				to_sort[i + 1] = tmp;
			}
			i++;
		}
	}
	return (to_sort);
}

void	print_export(char **sorted)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = NULL;
	value = NULL;
	if (sorted == NULL)
		return ;
	while (sorted[i])
	{
		if (ft_strchr(sorted[i], '='))
		{
			key = protected_split_grep_one(sorted[i], '=', 0);
			if (key == NULL)
				error_exit("Malloc failed", 1);
			value = sorted[i] + ft_strlen(key) + 1;
			if (key[0] != '?' && (key[0] != '_' || sorted[i][1] != '='))
			{
				write(STDOUT_FILENO, "declare -x ", 11);
				write(STDOUT_FILENO, key, ft_strlen(key));
				write(STDOUT_FILENO, "=\"", 2);
				write(STDOUT_FILENO, value, ft_strlen(value));
				write(STDOUT_FILENO, "\"\n", 2);
			}
			free(key);
			free(sorted[i]);
		}
		else
		{
			key = sorted[i];
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, key, ft_strlen(key));
			write(STDOUT_FILENO, "\n", 1);
			free(key);
			free(sorted[i]);
		}
		i++;
	}
	free(sorted);
}

int	execute_export(char **commands)
{
	int	i;

	i = 1;
	if (!commands[i])
	{
		print_export(bubble_sort(copy_array(g_info.env)));
	}
	while (commands[i])
	{
		if (ft_isalpha(commands[i][0]) || \
		(commands[i][0] == '_' && commands[i][1] != '='))
		{
			set_env_variable(commands[i]);
		}
		else if ((commands[i][0] != '_'))
		{
			write(STDERR_FILENO, "mickeyshell: export: `", 22);
			write(STDERR_FILENO, commands[i], ft_strlen(commands[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}
