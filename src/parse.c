/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/08 17:26:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>

int	count_pipes(char *str)
{
	int	i;
	int	j;
	int	q;
	int	quotes;

	i = 0;
	j = 0;
	q = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
        if ((str[i] == 34 || str[i] == 39) && q == 0)
        {
			q = 1;
			quotes++;
		}
		else if ((str[i] == 34 || str[i] == 39) && q == 1)
		{
			quotes++;
			q = 0;
		}
		if (str[i] == '|' && q == 0)
		{
			j++;
			i++;
		}
		else
			i++;
	}
	if ((i - quotes) == j + (quotes / 2)) //means there are only pipes on the cmd line.
	{
		if (i == 1) //only 1 pipe on cmd line
			printf("mickeyshell: syntax error near unexpected token `|'\n");
		else
			printf("mickeyshell: syntax error near unexpected token `||'\n");
		return(-1); //hier wel letten op leaks!
	}
	return (j);
}

char	**extend_dollars_remove_quotes(char **array)
{
	int	i;

	i = 0;
	while (array && array[i] != NULL)
	{
		array[i] = extend_dollars(array[i]);
		array[i] = remove_quotes(array[i]);
		i++;
	}
	return (array);
}

void	split_parts(t_part *part, t_part_split *part_split)
{
	int	i;

	i = 0;
	if (part->out_r != NULL)
		part_split->out_r = ft_strdup(part->out_r);
	if (part->out != NULL)
		part_split->out = ft_split_pipes(part->out, ' ');
	if (part->cmd != NULL)
		part_split->cmd = ft_split_pipes(part->cmd, ' ');
	if (part->in != NULL)
		part_split->in = ft_split_pipes(part->in, ' ');
	//Hiertussen checken op dollar!
	part_split->out = extend_dollars_remove_quotes(part_split->out);
	part_split->cmd = extend_dollars_remove_quotes(part_split->cmd);
	part_split->in = extend_dollars_remove_quotes(part_split->in);
}

int	assign_parts(t_part *part, char *str)
{
	int	i;
	int	start;
	int	len;
	char	*tmp;
	int	heredocs;
	int	q;

	i = 0;
	start = 0;
	len = 0;
	tmp = NULL;
	heredocs = 0;
	q = 0;
	while (i < ((int)ft_strlen(str)))
	{
		q = set_quote_flag(q, str[i]);
			//str[i] = ' ';
		if (str[i] == '>' && str[i + 1] != '>')//>, dus woord hierna is outfile
		{
			if (part->out_r == NULL)
				part->out_r = ft_strdup(">");
			else
				part->out_r = ft_strjoin(part->out_r, ">");
			str[i] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			start = i;
			while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || (q == 1)) && str[i] != '\0')
			{
				q = set_quote_flag(q, str[i]);
				i++;
			}
			len = i - start;
			tmp = ft_substr(str, start, len);
			tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->out == NULL)
				part->out = ft_strdup(tmp);
			else
			{
				part->out = ft_strjoin(part->out, " ");
				part->out = ft_strjoin(part->out, tmp);
			}
			free(tmp);
			str = set_space(str, start, len);
		}
		else if (str[i] == '>' && str[i + 1] == '>') //>>, dus woord hierna is outfile
		{
			if (part->out_r == NULL)
				part->out_r = ft_strdup("]");
			else
				part->out_r = ft_strjoin(part->out_r, "]");
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			start = i;
			while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || (q == 1)) && str[i] != '\0')
			{
				q = set_quote_flag(q, str[i]);
				i++;
			}
			len = i - start;
			tmp = ft_substr(str, start, len);
			tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->out == NULL)
				part->out = ft_strdup(tmp);
			else
			{
				part->out = ft_strjoin(part->out, " ");
				part->out = ft_strjoin(part->out, tmp);
			}
			free(tmp);
			str = set_space(str, i, len);
		}
		else if (str[i] == '<' && str[i + 1] != '<')//dus woord hierna is infile
		{
			str[i] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			start = i;
			while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || (q == 1)) && str[i] != '\0')
			{
				q = set_quote_flag(q, str[i]);
				i++;
			}
			len = i - start;
			tmp = ft_substr(str, start, len);
			tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->in == NULL)
				part->in = ft_strdup(tmp);
			else
			{
				part->in = ft_strjoin(part->in, " ");
				part->in = ft_strjoin(part->in, tmp);
			}
			free(tmp);
			str = set_space(str, start, len);
		}
		else if (str[i] == '<' && str[i + 1] == '<') //Bij heredoc <<, dus woord hierna is stopwoord
		{
			heredocs++;
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			tmp = handle_here_doc(str, i, heredocs);
			if (part->in == NULL)
				part->in = ft_strdup(tmp);
			else
			{
				part->in = ft_strjoin(part->in, " ");
				part->in = ft_strjoin(part->in, tmp);
			}
			free (tmp);
			len = calc_len_word_after(str, i);
			str = set_space(str, i, len);
			i = i + len;
		}
		else
			i++;
		start = 0;
		len = 0;
	}
	part->cmd = ft_strdup(str);
	return (heredocs);
}

void	set_zero_parts(t_part *part, t_part_split *part_split)
{
	part->in = NULL;
	part->out = NULL;
	part->cmd = NULL;
	part->out_r = NULL;
	part_split->in = NULL;
	part_split->out = NULL;
	part_split->cmd = NULL;
	part_split->out_r = NULL;
}

// int	make_parts(int count_pipe, int heredocs, t_part_split **part_split, char *input)
// {
// 	t_part *parts;
// 	int		i;
// 	char **input_split;

// 	i = 0;
// 	input_split = ft_split_pipes(input, '|');
// 	parts = malloc((count_pipe + 1) * sizeof(t_part));
// 	part_split = malloc((count_pipe + 1) * sizeof(t_part_split));

// 	// if (parts == NULL)
// 	// 	return ; // Hier malloc errors handlen!
// 	while (i < (count_pipe + 1))
// 	{
// 		set_zero_parts(&parts[i], part_split[i]);
// 		heredocs = assign_parts(&parts[i], input_split[i]);
// 		split_parts(&parts[i], (part_split)[i]);
// 		i++;
// 	}
// 	return (heredocs);
// }

// void	exec_minishell(char *input)
// {
// 	// char **input_split;
// 	t_part_split	*part_split;
// 	int	fd;
// 	int	pid;
// 	int status;
// 	int	count_pipe;
// 	int	i;
// 	int	heredocs;
// 	char 	*return_value;

// 	i = 0;
// 	heredocs = 0;
// 	part_split = NULL;
// 	fd = dup(0);
// 	// input_split = ft_split_pipes(input, '|');
// 	count_pipe = count_pipes(input);
// 	printf("Count_pipe: %d\n", count_pipe);

// 	// if (count_pipe < 0)
// 	// 	return ; // Hier error handling inbouwen!!
// 	heredocs = make_parts(count_pipe, heredocs, &part_split, input);
// 	printf("Count_pipe: %d\n", count_pipe);
// 	pid = executer(0, count_pipe + 1, fd, part_split);
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		return_value = ft_strjoin(ft_strdup("?="), ft_itoa(WEXITSTATUS(status)));
// 		set_env_variable(return_value);
// 	}
// 	i = 1;
// 	while (i < count_pipe + 1)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// 	delete_temp_heredoc_files(heredocs);
// }

void	exec_minishell(char *input)
{
	char **input_split;
	t_part *parts;
	t_part_split	*part_split;
	int	fd;
	int	pid;
	int status;
	int	count_pipe;
	int	i;
	int	heredocs;
	char	*tmp;
	char *return_value;

	i = 0;
	heredocs = 0;
	fd = dup(0);
	tmp = NULL;
	input_split = ft_split_pipes(input, '|');
	count_pipe = count_pipes(input);
	if (count_pipe < 0)
		return ;
	//printf("Number of actual pipes: %d\n", count_pipe);
	parts = malloc((count_pipe + 1) * sizeof(t_part));
	part_split = malloc((count_pipe + 1) * sizeof(t_part_split));
	if (parts == NULL)
		return ;
	while (i < (count_pipe + 1))
	{
		set_zero_parts(&parts[i], &part_split[i]);
		heredocs = assign_parts(&parts[i], input_split[i]);
		split_parts(&parts[i], &part_split[i]);
		//print_info(&parts[i]);
		i++;
	}
	pid = executer(0, count_pipe + 1, fd, part_split);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		return_value = ft_strjoin(ft_strdup("?="), ft_itoa(WEXITSTATUS(status)));
		set_env_variable(return_value);
	}
	i = 1;
	while (i < count_pipe + 1)
	{
		wait(NULL);
		i++;
	}
	delete_temp_heredoc_files(heredocs);

	// while (heredocs > 0)
	// {
	// 	tmp = ft_strjoin(".heredoc", ft_itoa(heredocs));
	// 	printf("Tmp name: %s\n", tmp);
	// 	unlink(tmp);
	// 	free(tmp);
	// 	heredocs--;
	// }
}

int	check_double_red(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_isred(str[i]) != 0)
		{
			while (ft_isred(str[i]) != 0)
			{
				i++;
				j++;
			}
			if (j == 2 && str[0] == '<' && str[1] == '>')
			{
				printf("mickeyshell: syntax error near unexpected token 'newline' [strchar: %c]\n", str[i-j+1]);
				return (-1);
			}
			if (j == 3 && (str[i-j+1] == '<'))
			{
				printf("mickeyshell: syntax error near unexpected token '<' [strchar: %c]\n", str[i-j+1]);
				return (-1);
			}
			else if (j == 3 && (str[i-j+1] == '>'))
			{
				printf("mickeyshell: syntax error near unexpected token '>' [strchar: %c]\n", str[i-j+1]);
				return (-1);
			}
			else if (j > 3 && (str[i-j+1] == '>'))
			{
				printf("mickeyshell: syntax error near unexpected token '>>' [strchar: %c]\n", str[i-j+1]);
				return (-1);
			}
			else if (j > 3 && (str[i-j+1] == '<'))
			{
				printf("mickeyshell: syntax error near unexpected token '<<' [strchar: %c]\n", str[i-j+1]);
				return (-1);
			}
			else
				j = 0;
		}
		i++;
	}
	return (0);
}
