/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 15:05:46 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h> //weggg
#include <sys/wait.h>

static void	request_next_line(char **buf)
{
	write(1, "> ", 2);
	*buf = get_next_line_shell(0);
}

char	*read_stdin_until(char *limiter)
{
	char	*input;
	char	*buf;

	input = ft_strdup("");
	if (input == NULL)
		error_exit("malloc failed", 1);
	request_next_line(&buf);
	if (buf == NULL && g_info.signal_status != 67)
		return (input);
	if (buf == NULL && g_info.signal_status == 67)
		return (NULL);
	while (!(ft_strncmp(buf, limiter, ft_strlen(limiter) - 1) == 0 && \
			ft_strlen(buf) == ft_strlen(limiter)))
	{
		input = ft_strjoin_fr(input, buf);
		if (input == NULL)
			error_exit("malloc failed", 1);
		free(buf);
		request_next_line(&buf);
		if (buf == NULL && g_info.signal_status != 67)
			return (input);
		if (buf == NULL && g_info.signal_status == 67)
			return (NULL);
	}
	free(buf);
	return (input);
}

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
	char	*input;
	int		readfd;
	struct sigaction	sa;

	(void)len;
	sa.sa_handler = &sig_handler_hd;
	input = NULL;
	g_info.signal_status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	readfd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (readfd < 0)
		error_exit("open", 1);
	rl_catch_signals = 0; //readline now doesn't install default signal handlers :)
	suppress_output_terminal();
	input = read_stdin_until(stop);
	if (input == NULL)
	{
		delete_temp_heredoc_files(heredocs);
		return (-1);
	}
	input = extend_dollars_hd(input);
	ft_putstr_fd(input, readfd);
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
