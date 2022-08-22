/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 13:49:34 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/19 14:57:35 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#define BUFFER_SIZE 20

char	*ft_charjoin(char *s1, char c)
{
	char	*sdef;
	int		i;

	i = 0;
	if (c == 0)
		return (0);
	if (s1)
		i = ft_strlen(s1);
	if (s1 == NULL)
	{
		sdef = malloc((2) * (sizeof(char)));
		if (sdef == NULL)
			return (NULL);
		sdef[0] = c;
		sdef[1] = '\0';
		return (sdef);
	}
	sdef = malloc((i + 2) * (sizeof(char)));
	if (sdef == NULL)
		return (NULL);
	sdef = joinstr_gnl(s1, c, sdef);
	free(s1);
	return (sdef);
}

char	*search_and_make(int fd, char *buf, t_gnl *gnl, t_gnl *stat)
{
	if (stat->flag == 1)
		return (NULL);
	while (buf[gnl->n] != '\n')
	{
		if ((buf[gnl->n] == '\0' || gnl->ret == 0))
		{
			gnl->ret = read(fd, buf, BUFFER_SIZE);
			if (gnl->ret <= 0)
			{
				if (gnl->nextline != NULL)
					return (buf);
				return (NULL);
			}
			buf[gnl->ret] = '\0';
			gnl->n = 0;
		}
		if (buf[gnl->n] == '\n')
			break ;
		gnl->nextline = ft_charjoin(gnl->nextline, buf[gnl->n]);
		if (gnl->nextline == NULL)
			stat->flag = 1;
		gnl->n++;
	}
	return (buf);
}

char	*loop_through_rest(char *buf, t_gnl *gnl, t_gnl *stat)
{
	while ((buf[gnl->n] != '\n') && (buf[gnl->n] != '\0'))
		gnl->n++;
	if (gnl->n < (BUFFER_SIZE - 1) && buf[gnl->n] != '\0')
	{
		gnl->nextline = ft_substr_gnl(buf, 0, gnl->n + 1, stat);
		if (stat->flag == 1)
			return (NULL);
		ft_memmove(buf, buf + gnl->n + 1, BUFFER_SIZE - gnl->n);
		return (buf);
	}
	return (NULL);
}

char	*gnl_arrange(int fd, t_gnl *gnl, t_gnl *stat, char *buf)
{
	if (stat->a == 1)
	{
		if (loop_through_rest(buf, gnl, stat) != NULL)
			return (gnl->nextline);
		if (stat->flag == 1)
			return (NULL);
		gnl->nextline = ft_substr_gnl(buf, 0, gnl->n, stat);
		if (stat->flag == 1)
			return (NULL);
		stat->a = 0;
	}
	search_and_make(fd, buf, gnl, stat);
	if (stat->flag == 1)
		return (NULL);
	if (buf[gnl->n] == '\n')
	{
		gnl->nextline = ft_charjoin(gnl->nextline, buf[gnl->n]);
		if (gnl->n < gnl->ret && (buf[gnl->n] != '\0'))
		{
			ft_memmove(buf, buf + gnl->n + 1, BUFFER_SIZE - gnl->n);
			stat->a = 1;
		}
	}
	return (buf);
}

char	*get_next_line_shell(int fd)
{
	t_gnl			gnl;
	static t_gnl	stat;
	static char		buf[BUFFER_SIZE + 1];

	gnl.ret = 0;
	gnl.n = 0;
	gnl.nextline = NULL;
	if (fd < 0 ||/* fd > OPEN_MAX ||*/ BUFFER_SIZE <= 0)
		return (NULL);
	gnl_arrange(fd, &gnl, &stat, buf);
	if (gnl.nextline == NULL)
		error_exit("malloc faild in get_next_line", 1);
	return (gnl.nextline);
}
