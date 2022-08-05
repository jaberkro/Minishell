/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/05 15:41:44 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	read_from_stdin(char *stop, char *hd_filename)
{
	int		cmp;
	char	*input;
	int		fd;

	cmp = 1;
	input = NULL;
	fd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0707);
	while (cmp != 0)
	{
		input = get_next_line(STDIN_FILENO);
		//if (input == NULL)
			//if_error(); //Hier zelf error handlen voor minishell???
		cmp = ft_strncmp(input, stop, ft_strlen(stop));
		if (cmp == 0)
			break ;
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
	//if (fd < 0)
		//if_error(); //Hier zelf error handlen voor minishell!
	len = calc_len_word_after(str, i);
	stop = malloc(len * sizeof(char));
	while (j < len)
	{
		stop[j] = str[i];
		i++;
		j++;
	}
	stop = remove_quotes(stop);
	read_from_stdin(stop, hd_filename);
	free (stop);
	return (hd_filename);
}
