/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 11:56:38 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h> //weggg
#include <sys/wait.h>

static char	*extend_dollars_hd(char *input)
{
	char	*tmp;

	tmp = ft_strdup(input);
	free(input);
	input = extend_dollars(tmp);
	free (tmp);
	return (input);
}


static int	read_from_stdin(char *stop, char *hd_filename, int len, int heredocs)
{
	int		cmp;
	char	*input;
	int		readfd;
	struct sigaction	sa;
	int	status;

	sa.sa_handler = &sig_handler_hd;
	cmp = 1;
	input = NULL;
	readfd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (readfd < 0)
		error_exit("open failed", 1);
	g_info.sigflag = status;
	rl_catch_signals = 0; //readline now doesn't install default signal handlers :)
	suppress_output_terminal();
	while (cmp != 0)
	{
		input = readline("> ");
		input = ft_strjoin_fr(input, "\n");
		if (input == NULL)
		{
			close(readfd);
			exit (0);
		}
		cmp = ft_strncmp(input, stop, len + 1);
		if (cmp == 0)
			break ;
		input = extend_dollars_hd(input);
		ft_putstr_fd(input, readfd);
		free (input);
	}
	free (input);
	close(readfd);
	return (0);
}

char	*handle_here_doc(char *str, int i, int heredocs)
{
	char	*stop;
	int		j;
	int		len;
	char	*hd_num;
	char	*hd_filename;

	len = 0;
	j = 0;
	hd_num = ft_itoa(heredocs);
	hd_filename = ft_strjoin(".heredoc", hd_num);
	len = calc_len_word_after(str, i);
	stop = malloc((len + 1) * sizeof(char));
	while (j < len)
	{
		stop[j] = str[i];
		i++;
		j++;
	}
	stop[j] = '\n';
	stop = remove_quotes(stop);
	if (read_from_stdin(stop, hd_filename, len, heredocs) < 0)
		return (NULL);	
	free (stop);
	free (hd_num);
	return (hd_filename);
}
