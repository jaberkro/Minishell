/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/22 15:20:10 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_info(t_part *parts)
{
	printf("START\n");
	printf("infile: %s\n", parts->in);
	printf("cmd: %s\n", parts->cmd);
	printf("outfile: %s\n", parts->out);
	printf("in_r: %c\n", parts->in_r);
	printf("out_r: %c\n", parts->out_r);
	printf("END\n");
}

int	count_pipes(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			j++;
			i++;
		}
		else
			i++;
	}
	return (j);
}

void	assign_parts(t_part *part, char *str)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	start = 0;
	len = 0;
	while (i < ((int)ft_strlen(str)))
	{
		//printf("Str to be checked: %s\n", str);
		if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')//dus woord hierna is outfile
		{
			part->in_r = '>';
			str[i] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			len = calc_len_word_after(str, i);
			part->out = ft_substr(str, i, len);
			part->out = ft_strtrim(part->out, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			str = set_space(str, i, len);
			i = i + len;
		}
		else if (str[i] == '>' && str[i + 1] == '>') //dus woord hierna is outfile
		{
			part->in_r = ']';
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			len = calc_len_word_after(str, i);
			part->out = ft_substr(str, i, len);
			str = set_space(str, i, len);
			i = i + len;
		}
		else if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')//dus woord hierna is infile
		{
			part->out_r = '<';
			str[i] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			len = calc_len_word_after(str, i);
			part->in = ft_substr(str, i, len);
			str = set_space(str, i, len);
			i = i + len;
		}
		else if (str[i] == '<' && str[i + 1] == '<') //Bij heredoc <<, dus woord hierna is stopwoord
		{
			part->out_r = '[';
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			len = calc_len_word_after(str, i);
			str = set_space(str, i, len);
			i = i + len;
		}
		else
			i++;
		len = 0;
		//printf("Main string after setting spaces: -%s-\n", str);
	}
	part->cmd = ft_strdup(str);
}

void	set_zero_parts(t_part *part)
{
	part->in = NULL;
	part->out = NULL;
	part->cmd = NULL;
	part->in_r = 0;
	part->out_r = 0;
}

void	exec_minishell(char *input)
{
	char **input_split;
	t_part *parts;
	int	fd;
	int	count_pipe;
	int	i;

	i = 0;
	fd = dup(0);
	input_split = ft_split(input, '|'); //REKENING HOUDEN MET PIPE TUSSEN QUOTES
	count_pipe = count_pipes(input);
	parts = malloc((count_pipe + 1) * sizeof(t_part));
	if (parts == NULL)
		return ;
	while (i < (count_pipe + 1))
	{
		set_zero_parts(&parts[i]);
		assign_parts(&parts[i], input_split[i]);
		print_info(&parts[i]);
		i++;
	}
	//HIER EXECUTER AANROEPEN: bijv. executer(0, i, fd, parts);
}

void	run_minishell()
{
	char *str;
	int	cmp;

	cmp = -1;
	while (cmp != 0)
	{
		str = readline("mickeyshell> ");
		cmp = ft_strncmp(str, "exit\0", 5);
		if (cmp == 0)
			break ;
		exec_minishell(str);
		free (str);
	}
	free (str);
}

int	main()
{
	run_minishell();
}