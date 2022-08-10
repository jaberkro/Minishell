/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/29 17:30:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/10 14:01:33 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h> //wegggg

void	delete_temp_heredoc_files(int heredocs)
{
	char *tmp;
	char *itoa_hd;

	itoa_hd = NULL;
	tmp = NULL;
	while (heredocs > 0)
	{
		itoa_hd = ft_itoa(heredocs);
		tmp = ft_strjoin(".heredoc", itoa_hd);//ft_itoa(heredocs));
		printf("Tmp name: %s\n", tmp);
		unlink(tmp);
		free(itoa_hd);
		free(tmp);
		heredocs--;
	}
}

void	read_from_stdin(char *stop, char *hd_filename, int len)
{
	int		cmp;
	char	*input;
	int		fd;

	cmp = 1;
	input = NULL;
	fd = open(hd_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	while (cmp != 0)
	{
		input = get_next_line(STDIN_FILENO);
		printf("input = [%s]\n", input);

		//if (input == NULL)
			//if_error(); //Hier zelf error handlen voor minishell???
		cmp = ft_strncmp(input, stop, len);//ft_strlen(stop));
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
	printf("Stop = [%s]\n", stop);
	read_from_stdin(stop, hd_filename, len);
	free (stop);
	free (hd_num);
	return (hd_filename);
}
