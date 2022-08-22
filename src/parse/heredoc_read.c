/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_read.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 15:36:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 18:05:38 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	request_next_line(char **buf)
{
	write(1, "> ", 2);
	*buf = get_next_line_shell(0);
}

/**
 * @brief calls get_next_line and compares the line written to the stopword
 * 
 * @param limiter 	the stop word (delimiter) to end heredoc mode
 * @return char* 	the input from heredoc mode, NULL in case of earlier abort
 */
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

/**
 * @brief sets the signals and terminal settings for heredoc mode, 
 * reads and write the heredoc input to the temporary heredoc files.
 * 
 * @param stop 			the word with which heredoc input ends
 * @param hd_filename 	the temporary heredoc file to write to
 * @param heredocs 		the number of temp heredoc files present
 * @return int 			0 on succes, -1 on abort
 */
int	read_from_stdin(char *stop, char *hd_filename, int heredocs)
{
	char				*input;
	int					readfd;

	input = NULL;
	g_info.signal_status = 0;
	set_sigs_hd();
	readfd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (readfd < 0)
		error_exit("open", 1);
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
