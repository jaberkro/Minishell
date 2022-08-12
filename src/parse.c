/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/12 14:34:13 by jaberkro      ########   odam.nl         */
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
			j++;
		i++;
	}
	if (((i - quotes) == j + (quotes / 2)) || q == 1) //means there are only pipes on the cmd line.
	{
		printf("mickeyshell: wrong use of quotes and/or pipes\n");
		return(-1);
	}
	return (j);
}

char	**extend_dollars_remove_quotes(char **array)
{
	int		i;
	char	*tmp;

	i = 0;
	while (array && array[i] != NULL)
	{
		tmp = array[i];
		array[i] = extend_dollars(tmp);
		free(tmp);
		array[i] = remove_quotes(array[i]);
		i++;
	}
	return (array);
}


// void 	print_part_split(t_part_split *part_split)
// {
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		if (part_split->in[i] != NULL)
// 			printf("part_split->in: [%s]", part_split->in[i]);
// 		if (part_split->cmd[i] != NULL)
// 			printf("part_split->cmd: [%s]", part_split->cmd[i]);
// 		if (part_split->out[i] != NULL)
// 			printf("part_split->out: [%s]", part_split->out[i]);
// 		if (part_split->out_r != NULL)
// 			printf("part_split->out_r: [%s]", part_split->out_r);
// 		i++;
// 	}
// }



void	split_parts(t_part *part, t_part_split *part_split)
{
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
	// printf("Block out_r: [%s]\n", part_split->out_r);
}

char	*to_outfile(t_part *part, char *str, int *q_ptr, int *i_ptr)
{
	int	start;
	int	len;
	char *tmp;
	int	i;
	int	q;

	start = 0;
	len = 0;
	tmp = NULL;
	i = *i_ptr;
	q = *q_ptr;
	if (part->out_r == NULL)
		part->out_r = ft_strdup(">");
	else
		part->out_r = ft_strjoin_fr(part->out_r, ">");
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
	tmp = ft_strtrim_fr(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
	if (part->out == NULL)
		part->out = ft_strdup(tmp);
	else
	{
		part->out = ft_strjoin_fr(part->out, " ");
		part->out = ft_strjoin_fr(part->out, tmp);
	}
	free(tmp);
	str = set_space(str, start, len);
	*q_ptr = q;
	*i_ptr = i;
	return (str);
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
		// printf("before: q: %d, i: %d\n", q, i);
		if (str[i] == '>' && str[i + 1] != '>')//>, dus woord hierna is outfile
			str = to_outfile(part, str, &q, &i);
		else if (str[i] == '>' && str[i + 1] == '>') //>>, dus woord hierna is outfile
		{
			if (part->out_r == NULL)
				part->out_r = ft_strdup("]");
			else
				part->out_r = ft_strjoin_fr(part->out_r, "]");
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
			tmp = ft_strtrim_fr(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->out == NULL)
				part->out = ft_strdup(tmp);
			else
			{
				part->out = ft_strjoin_fr(part->out, " ");
				part->out = ft_strjoin_fr(part->out, tmp);
			}
			// printf("Part out: [%s]\n", part->out);
			free(tmp);
			// printf("Str before set: [%s], i: %d, len: %d\n", str, i, len);
			str = set_space(str, i - len, len);
			// printf("Str after set: [%s], i: %d, len: %d\n", str, i, len);
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
			tmp = ft_strtrim_fr(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->in == NULL)
				part->in = ft_strdup(tmp);
			else
			{
				part->in = ft_strjoin_fr(part->in, " ");
				part->in = ft_strjoin_fr(part->in, tmp);
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
				part->in = ft_strjoin_fr(part->in, " ");
				part->in = ft_strjoin_fr(part->in, tmp);
			}
			free (tmp);
			len = calc_len_word_after(str, i);
			str = set_space(str, i, len);
			i = i + len;
		}
		else
			i++;
		// start = 0;
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

void	if_exited(int status)
{
	char *itoa_exit;
	char *return_value;

	itoa_exit = ft_itoa(WEXITSTATUS(status));
	return_value = ft_strjoin("?=", itoa_exit);
	free(itoa_exit);
	set_env_variable(return_value);
	free(return_value);
}

void	clean_up(int heredocs, char **input_split, t_part_split *part_split, int count)
{
	int	i;

	i = 0;
	free_array(input_split);
	while (i < count)
	{
		free_struct_split(&part_split[i]);
		free (&part_split[i]);
		i++;
	}
	delete_temp_heredoc_files(heredocs);
}

void	call_executer(int count_pipe, t_part_split *part_split)
{
	int pid;
	int fd;
	int	i;
	int	status;
	
	fd = dup(0);
	i = 1;
	// print_part_split(part_split);

	pid = executer(0, count_pipe + 1, fd, part_split);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		if_exited(status);
	while (i < count_pipe + 1)
	{
		wait(NULL);
		i++;
	}
}

int	set_fill_split_parts(char **input_split, int count_pipe, t_part_split *part_split, int heredocs)
{
	int	i;
	t_part *parts;

	i = 0;
	parts = malloc((count_pipe + 1) * sizeof(t_part));
	if (parts == NULL)
		return (-1);
	while (i < (count_pipe + 1))
	{
		set_zero_parts(&parts[i], &part_split[i]);
		heredocs = assign_parts(&parts[i], input_split[i]);
		split_parts(&parts[i], &part_split[i]);
		// print_part_split(&part_split[i]);
		i++;
	}
	// if (count_pipe + 1 == 1)
	// {
	// 	single_executer(0, count_pipe + 1, fd, part_split);
	// 	delete_temp_heredoc_files(heredocs);
	// 	return ;
	// }
	// else
	// {
	
	
	// free_array(input_split);
	// free_struct(parts);
	return (heredocs);
}

void	exec_minishell(char *input)
{
	char **input_split;
	t_part_split	*part_split;
	int	count_pipe;
	int	heredocs;

	heredocs = 0;
	input_split = ft_split_pipes(input, '|');
	count_pipe = count_pipes(input);
	if (count_pipe < 0 || input_split == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	part_split = malloc((count_pipe + 1) * sizeof(t_part_split));
	if (part_split == NULL)
		error_exit("mickeyshell: malloc failed", 1);
	heredocs = set_fill_split_parts(input_split, count_pipe, part_split, heredocs);
	if (heredocs < 0)
		error_exit("mickeyshell: malloc failed", 1);
	call_executer(count_pipe, part_split);
	clean_up(heredocs, input_split, part_split, count_pipe); //removed +1 12/8
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
			if ((j == 2 && str[0] == '<' && str[1] == '>') || (j == 3 && \
			(str[i - j + 1] == '<')) || (j == 3 && (str[i - j + 1] == '>')))
				return (-1);
			else if ((j > 3 && (str[i - j + 1] == '>')) || \
			(j > 3 && (str[i - j + 1] == '<')))
				return (-1);
			else
				j = 0;
		}
		i++;
	}
	return (0);
}
