/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_parts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 16:30:34 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 17:07:34 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*set_value(char *to_set, char *str, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	if (tmp == NULL)
		error_exit("malloc", 1);
	tmp = ft_strtrim_fr(tmp, " ");
	if (tmp == NULL)
		error_exit("malloc", 1);
	if (to_set == NULL)
		to_set = ft_strdup(tmp);
	else
	{
		to_set = ft_strjoin_fr(to_set, " ");
		if (to_set == NULL)
			error_exit("malloc", 1);
		to_set = ft_strjoin_fr(to_set, tmp);
		if (to_set == NULL)
			error_exit("malloc", 1);
	}
	free(tmp);
	return (to_set);
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
	tmp = handle_here_doc(str, i, heredocs);
	if (tmp == NULL)
		return (NULL);
	if (part->in == NULL)
		part->in = ft_strdup(tmp);
	else
	{
		part->in = ft_strjoin_fr(part->in, " ");
		if (part->in == NULL)
			error_exit("malloc", 1);
		part->in = ft_strjoin_fr(part->in, tmp);
	}
	if (part->in == NULL)
		error_exit("malloc", 1);
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
	part->in = set_value(part->in, str, start, len);
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
	if (part->out_r == NULL)
		part->out_r = ft_strdup("]");
	else
		part->out_r = ft_strjoin_fr(part->out_r, "]");
	if (part->out == NULL)
		error_exit("malloc", 1);
	str[i] = ' ';
	str[i + 1] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	start = i;
	while (((q == 0 && ft_isspace(str[i]) == 0 && ft_isred(str[i]) == 0) || \
	(q == 1)) && str[i] != '\0')
	{
		q = set_quote_flag(q, str[i]);
		i++;
	}
	len = i - start;
	part->out = set_value(part->out, str, start, len);
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
	if (part->out_r == NULL)
		part->out_r = ft_strdup(">");
	else
		part->out_r = ft_strjoin_fr(part->out_r, ">");
	if (part->out_r == NULL)
		error_exit("malloc", 1);
	str[i] = ' ';
	while (ft_isspace(str[i]) != 0)
		i++;
	start = i;
	while (((q == 0) && (ft_isspace(str[i]) == 0) && (ft_isred(str[i]) == 0) && (str[i] != '\0')) || \
	((q != 0) && str[i] != '\0'))//laatste toegvd
	{
		q = set_quote_flag(q, str[i]);
		printf("str[i]: [%c], q: %d\n", str[i], q);
		i++;
	}
	len = i - start;
	part->out = set_value(part->out, str, start, len);
	str = set_space(str, start, len);
	*q_ptr = q;
	*i_ptr = i;
	return (str);
}
