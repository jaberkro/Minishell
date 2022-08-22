/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 15:19:22 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
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
	malloc_check(input);
	request_next_line(&buf);
	if (buf == NULL && g_info.signal_status != 67)
		return (input);
	if (buf == NULL)
		return (NULL);
	while (!(ft_strncmp(buf, limiter, ft_strlen(limiter) - 1) == 0 && \
			ft_strlen(buf) == ft_strlen(limiter)))
	{
		input = ft_strjoin_fr(input, buf);
		malloc_check(input);
		free(buf);
		request_next_line(&buf);
		if (buf == NULL && g_info.signal_status != 67)
			return (input);
		if (buf == NULL)
			return (NULL);
	}
	free(buf);
	return (input);
}

static char	*extend_dollars_hd(char *input)
{
	char	*tmp;

	tmp = ft_strdup(input);
	malloc_check(tmp);
	free(input);
	input = extend_dollars(tmp);
	free (tmp);
	return (input);
}

static void	set_sigs(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler_hd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static int	read_from_stdin(char *stop, char *hd_filename, int heredocs)
{
	char				*input;
	int					readfd;

	input = NULL;
	g_info.signal_status = 0;
	set_sigs();
	readfd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (readfd < 0)
		error_exit("open", 1);
	rl_catch_signals = 0;
	set_output_terminal(0);
	input = read_stdin_until(stop);
	set_output_terminal(1);
	if (input == NULL)
	{
		delete_temp_heredoc_files(heredocs);
		return (-1);
	}
	input = extend_dollars_hd(input);
	ft_putstr_fd(input, readfd);
	free (input);
	protected_close(readfd);
	return (0);
}

static char	*get_stop(char *str, int i)
{
	int		j;
	int		len;
	char	*stop;

	j = 0;
	len = calc_len_word_after(str, i);
	stop = malloc((len + 1) * sizeof(char));
	malloc_check(stop);
	while (j < len)
	{
		stop[j] = str[i];
		i++;
		j++;
	}
	stop[j] = '\n';
	stop = remove_quotes(stop);
	return (stop);
}

char	*handle_heredoc(char *str, int i, int heredocs)
{
	char	*stop;
	char	*hd_num;
	char	*hd_filename;

	hd_num = ft_itoa(heredocs);
	malloc_check(hd_num);
	hd_filename = ft_strjoin(".heredoc", hd_num);
	malloc_check(hd_filename);
	stop = get_stop(str, i);
	if (read_from_stdin(stop, hd_filename, heredocs) < 0)
		return (NULL);
	free (stop);
	free (hd_num);
	return (hd_filename);
}
