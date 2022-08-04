/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/04 17:34:59 by jaberkro      ########   odam.nl         */
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
	// printf("START\n");
	// printf("infile: %s\n", parts->in);
	// printf("cmd: -%s-\n", parts->cmd);
	// printf("outfile: %s\n", parts->out);
	//printf("in_r: %c\n", parts->in_r);
	printf("out_r: %s\n", parts->out_r);
	// printf("END\n");
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

void	split_parts(t_part *part, t_part_split *part_split)
{
	int	i;

	i = 0;
	if (part->out_r != NULL)
		part_split->out_r = ft_strdup(part->out_r);
	if (part->out != NULL)
		part_split->out = ft_split_pipes(part->out, ' ');
	// printf("XXXX %s XXXX\n", part->cmd);
	if (part->cmd != NULL)
		part_split->cmd = ft_split_pipes(part->cmd, ' ');
	// printf("XXXX %s XXXX\n", part_split->cmd[0]);
	// printf("XXXX %s XXXX\n", part_split->cmd[1]);
	if (part->in != NULL)
		part_split->in = ft_split_pipes(part->in, ' ');
	//Hiertussen checken op dollar!
	while (part_split->out && part_split->out[i] != NULL)
	{
		part_split->out[i] = extend_dollars(part_split->out[i]);
		part_split->out[i] = remove_quotes(part_split->out[i]);
		// printf("part_split->out[%d]: -%s-\n", i, part_split->out[i]);
		i++;
	}
	i = 0;
	while (part_split->cmd && part_split->cmd[i] != NULL)
	{
		part_split->cmd[i] = extend_dollars(part_split->cmd[i]);
		part_split->cmd[i] = remove_quotes(part_split->cmd[i]);
		// printf("part_split->cmd[%d]: -%s-\n", i, part_split->cmd[i]);
		i++;
	}
	i = 0;
	while (part_split->in && part_split->in[i] != NULL)
	{
		part_split->in[i] = extend_dollars(part_split->in[i]);
		part_split->in[i] = remove_quotes(part_split->in[i]);
		// printf("part_split->in[%d]: -%s-\n", i, part_split->in[i]);
		i++;
	}
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
		if ((str[i] == 34 || str[i] == 39) && q == 0)
			q = 1;
		else if ((str[i] == 34 || str[i] == 39) && q == 1)
			q = 0;
			//str[i] = ' ';
		if (str[i] == '>' && str[i + 1] != '>')//>, dus woord hierna is outfile
		{
			if (part->out_r == NULL)
				part->out_r = ft_strdup(">");
			else
				part->out_r = ft_strjoin(part->out_r, ">");
			str[i] = ' ';
			//printf("Set to space:: i = %d, str[i] = %c\n", i, str[i]);
			while (ft_isspace(str[i]) != 0)
				i++;
			start = i;
			while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || (q == 1)) && str[i] != '\0')
			{
			//	printf("IN LOOP: i = %d, str[i] = %c, q = %d\n", i, str[i], q);
				if ((str[i] == 34 || str[i] == 39) && q == 0)
					q = 1;
				else if ((str[i] == 34 || str[i] == 39) && q == 1)
					q = 0;
				i++;
			}
			//len = calc_len_word_after(str, i);
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
			//i = i + len;
		}
		else if (str[i] == '>' && str[i + 1] == '>') //>>, dus woord hierna is outfile
		{
			// part->out_r = ']';
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
				// printf("IN LOOP: i = %d, str[i] = %c, q = %d\n", i, str[i], q);
				if ((str[i] == 34 || str[i] == 39) && q == 0)
					q = 1;
				else if ((str[i] == 34 || str[i] == 39) && q == 1)
					q = 0;
				i++;
			}
			//len = calc_len_word_after(str, i);
			// part->out = ft_substr(str, i, len);
			len = i - start;
			tmp = ft_substr(str, start, len);
			tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			// tmp = ft_substr(str, i, len);
			// tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->out == NULL)
				part->out = ft_strdup(tmp);
			else
			{
				part->out = ft_strjoin(part->out, " ");
				part->out = ft_strjoin(part->out, tmp);
			}
			free(tmp);
			str = set_space(str, i, len);
			//i = i + len;
		}
		else if (str[i] == '<' && str[i + 1] != '<')//dus woord hierna is infile
		{
			str[i] = ' ';
			while (ft_isspace(str[i]) != 0)
				i++;
			start = i;
			while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || (q == 1)) && str[i] != '\0')
			{
				// printf("IN LOOP: i = %d, str[i] = %c, q = %d\n", i, str[i], q);
				if ((str[i] == 34 || str[i] == 39) && q == 0)
					q = 1;
				else if ((str[i] == 34 || str[i] == 39) && q == 1)
					q = 0;
				i++;
			}
			//len = calc_len_word_after(str, i);
			len = i - start;
			tmp = ft_substr(str, start, len);
			// printf("Len = %d, start = %d, i = %d\n", len, start, i);
			tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			// tmp = ft_substr(str, i, len);
			// tmp = ft_strtrim(tmp, " "); //Voor het geval meerdere spaties tussen de woorden zaten
			if (part->in == NULL)
				part->in = ft_strdup(tmp);
			else
			{
				part->in = ft_strjoin(part->in, " ");
				part->in = ft_strjoin(part->in, tmp);
			}
			free(tmp);
			// printf("HIERO: i = %d, str[i] = %c, str = %s\n", i, str[i], part->in);

			str = set_space(str, start, len);
			//i = i + len;
		}
		else if (str[i] == '<' && str[i + 1] == '<') //Bij heredoc <<, dus woord hierna is stopwoord
		{
			heredocs++;
			// printf("Value of heredocs: %d\n", heredocs);
			//part->in_r = '[';
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
		// printf("Set to space: str = -%s-\n", str);

		start = 0;
		len = 0;
		//printf("Main string after setting spaces: -%s-\n", str);
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
		// print_info(&parts[i]);
		i++;
	}
	pid = executer(0, count_pipe + 1, fd, part_split);
	waitpid(pid, &status, 0);
	i = 1;
	while (i < count_pipe + 1)
	{
		wait(NULL);
		i++;
	}
	while (heredocs > 0)
	{
		tmp = ft_strjoin(".heredoc", ft_itoa(heredocs));
		printf("Tmp name: %s\n", tmp);
		unlink(tmp);
		free(tmp);
		heredocs--;
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
		if (str != NULL && str[0])
		{
			add_history(str);
			run_minishell(str); 
		}
		free (str);
	}
	return (0); //Hier exitcode invullen?
}