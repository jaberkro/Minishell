/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 10:28:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 17:45:40 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief checks if a char ** is sorted alphabetically
 * 
 * @param to_check 	the char ** to check
 * @return int 		1 if sorted, 0 if not sorted
 */
static int	is_sorted(char **to_check)
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

/**
 * @brief bubble sort algorithm to sort a char **
 * 
 * @param to_sort 	the char ** to sort
 * @return char** 	the sorted char **
 */
static char	**bubble_sort(char **to_sort)
{
	char	*tmp;
	int		i;
	int		j;

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

/**
 * @brief prints one line of export with a key and value
 * 
 * @param to_print the line to print
 */
static void	print_key_value(char *to_print)
{
	char	*key;
	char	*value;

	key = protected_split_grep_one(to_print, '=', 0);
	if (key == NULL)
		error_exit("malloc failed", 1);
	value = ft_strdup(to_print + ft_strlen(key) + 1);
	if ((key[0] != '?' && key[0] != '_' ) || to_print[1] != '=')
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	free(key);
	free(value);
	free(to_print);
}

/**
 * @brief prints as export depending on if ther is an '=' sign in the string
 * 
 * @param sorted 	the sorted char ** to be printed
 */
static void	print_export(char **sorted)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (sorted[i])
	{
		if (ft_strchr(sorted[i], '='))
			print_key_value(sorted[i]);
		else
		{
			key = ft_strdup(sorted[i]);
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(key, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(key);
			free(sorted[i]);
		}
		i++;
	}
	free(sorted);
}

/**
 * @brief if export has no arguments, it will print the sorted env list.
 * If export has arguments it will export those to the env list
 * 
 * @param commands 	the arguments to export
 * @return int 		1 in case of invalid input, 0 if everything went fine
 */
int	execute_export(char **commands, int max)
{
	int	i;

	i = 1;
	(void)max;
	if (!commands[i])
		print_export(bubble_sort(copy_array(g_info.env)));
	while (commands[i])
	{
		if (ft_isalpha(commands[i][0]) || \
		(commands[i][0] == '_' && commands[i][1] != '='))
		{
			set_env_variable(commands[i]);
			if (ft_strncmp(commands[i], "PATH", 4) == 0)
				g_info.paths = get_paths();
		}
		else if ((commands[i][0] != '_'))
		{
			ft_putstr_fd("mickeyshell: export: `", STDERR_FILENO);
			ft_putstr_fd(commands[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
