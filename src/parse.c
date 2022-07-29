/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/29 17:45:33 by bsomers       ########   odam.nl         */
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
	// printf("i: %d, quotes: %d, j: %d", i, quotes, j);
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
		if (str[i] == 34 || str[i] == 39)
			str[i] = ' ';
		//printf("Str to be checked: %s\n", str);
		if (str[i] == '>' && str[i + 1] != '>' && (i > 0 && str[i - 1] != '>'))//dus woord hierna is outfile
		{
			part->out_r = '>';
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
			part->out_r = ']';
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			len = calc_len_word_after(str, i);
			part->out = ft_substr(str, i, len);
			str = set_space(str, i, len);
			i = i + len;
		}
		else if (str[i] == '<' && str[i + 1] != '<' && (i > 0 && str[i - 1] != '<'))//dus woord hierna is infile
		{
			part->in_r = '<';
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
			part->in_r = '[';
			str[i] = ' ';
			str[i + 1] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			handle_here_doc(str, i);
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
	int	pid;
	int status;
	int	count_pipe;
	int	i;

	i = 0;
	fd = dup(0);
	input_split = ft_split_pipes(input, '|');
	count_pipe = count_pipes(input);
	if (count_pipe < 0)
		return ;
	printf("Number of actual pipes: %d\n", count_pipe);
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
	pid = executer(0, count_pipe + 1, fd, parts);
	waitpid(pid, &status, 0);
	i = 1;
	while (i < count_pipe + 1)
	{
		wait(NULL);
		i++;
	}
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

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	run_minishell(char *str)
{
	signal(SIGQUIT, SIG_IGN);
	if (ft_isemptyline(str) == 0)
		return ;
	if (check_double_red(str) < 0)
		return ;
	exec_minishell(str);
}

int	main()
{
	extern char **environ;
	char *str;
	int	cmp;
	struct sigaction	sa;

	rl_catch_signals = 0; //readline now doesn't install default signal handlers :)
	sa.sa_handler = &sig_handler;
	cmp = -1;
	init_global(environ);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		sigaction(SIGINT, &sa, NULL);
		str = readline("minishell> ");
		if (str == NULL) //which means EOF is encountered (that happens when ctrl-D is pressed)
		{
			printf("exit\n");
			sigaction(SIGQUIT, &sa, NULL);
			return (0);
		}
		cmp = ft_strncmp(str, "exit\0", 5);
		if (cmp == 0)
		{
			printf("exit\n");
			return (0);
		}
		if (str != NULL)
			run_minishell(str);
		free (str);
	}
	return (0); //Hier exitcode invullen?
}