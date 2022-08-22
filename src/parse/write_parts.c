/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_parts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:30:34 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 15:52:02 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*assign_heredoc_part(char *str, char *tmp)
{
	if (str == NULL)
		str = ft_strdup(tmp);
	else
	{
		str = ft_strjoin_fr(str, " ");
		malloc_check(str);
		str = ft_strjoin_fr(str, tmp);
	}
	malloc_check(str);
	return (str);
}

char	*from_heredoc(t_part *part, char *str, int heredocs, int *i_ptr)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = *i_ptr;
	tmp = NULL;
	str[i] = ' ';
	str[i + 1] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	tmp = handle_heredoc(str, i, heredocs);
	if (tmp == NULL)
		return (NULL);
	part->in = assign_heredoc_part(part->in, tmp);
	free (tmp);
	len = calc_len_word_after(str, i);
	str = set_space(str, i, len);
	i = i + len;
	return (str);
}

char	*from_infile(t_part *part, char *str, int *q_ptr, int *i_ptr)
{
	int	start;
	int	len;
	int	i;
	int	q;

	start = *i_ptr;
	len = 0;
	i = *i_ptr;
	q = *q_ptr;
	str[i] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || \
	(q == 1)) && str[i] != '\0')
	{
		q = set_quote_flag(q, str[i]);
		i++;
	}
	len = i - start;
	part->in = assign_filename(part->in, str, start, len);
	str = set_space(str, start, len);
	*q_ptr = q;
	*i_ptr = i;
	return (str);
}

char	*to_outfile_app(t_part *part, char *str, int *q_ptr, int *i_ptr)
{
	int	start;
	int	len;
	int	i;
	int	q;

	start = 0;
	len = 0;
	i = *i_ptr;
	q = *q_ptr;
	part->out_r = assign_redirector(part->out_r, "]");
	str[i] = ' ';
	str[i + 1] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	start = i;
	loop_to_end_word(&i, &q, str);
	len = i - start;
	part->out = assign_filename(part->out, str, start, len);
	str = set_space(str, i - len, len);
	*q_ptr = q;
	*i_ptr = i;
	return (str);
}

char	*to_outfile(t_part *part, char *str, int *q_ptr, int *i_ptr)
{
	int	start;
	int	len;
	int	i;
	int	q;

	start = 0;
	len = 0;
	i = *i_ptr;
	q = *q_ptr;
	part->out_r = assign_redirector(part->out_r, ">");
	str[i] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	start = i;
	loop_to_end_word(&i, &q, str);
	len = i - start;
	part->out = assign_filename(part->out, str, start, len);
	str = set_space(str, start, len);
	*q_ptr = q;
	*i_ptr = i;
	return (str);
}
