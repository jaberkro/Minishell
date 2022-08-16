/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/16 16:36:57 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*extend_dollars_hd(char *input)
{
	char	*tmp;

	tmp = ft_strdup(input);
	free(input);
	input = extend_dollars(tmp);
	free (tmp);
	return (input);
}

static void	read_from_stdin(char *stop, char *hd_filename, int len)
{
	int		cmp;
	char	*input;
	int		fd;

	cmp = 1;
	input = NULL;
	fd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		error_exit("open failed", 1);
	while (cmp != 0)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			error_exit("malloc failed", 1);
		cmp = ft_strncmp(input, stop, len + 1);
		if (cmp == 0)
			break ;
		input = extend_dollars_hd(input);
		ft_putstr_fd(input, fd);
		free (input);
	}
	free (input);
	close(fd);
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
	read_from_stdin(stop, hd_filename, len);
	free (stop);
	free (hd_num);
	return (hd_filename);
}
