/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/29 17:46:39 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	handle_here_doc(char *str, int i)
{
	int		fd;
	char	*input;
	int		cmp;
    char	*stop;
    int     j;
	int		len;

	len = 0;
	cmp = 1;
	j = 0;
	input = NULL;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0707);
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
	while (cmp != 0)
	{
		input = get_next_line(STDIN_FILENO);
		//if (input == NULL)
			//if_error();
		cmp = ft_strncmp(input, stop, len);
		if (cmp == 0)
			break ;
		ft_putstr_fd(input, fd);
		free (input);
	}
	free (input);
	close(fd); //Moet ik deze wel closen? Wat wilt de executer ontvangen?
}