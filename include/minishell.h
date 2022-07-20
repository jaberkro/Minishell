/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 17:35:37 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stdio.h>

/*
	t_part stores information about one part of the user input seperated by pipes
	@in contains the name of the inputfile. 
	@cmd contains the commands to be executed. 
	@out contains the name of the outputfile. 
	@in_r shows the sign before the infile. < or [
	@out_r shows the sign before the outfile. > or ]
*/
typedef struct s_part
{
	char	*in;
	char	*cmd;
	char	*out;
	char	in_r;
	char	out_r;
}	t_part;

void	error_exit(char *message, int exit_code);
int		executer(int i, int max, int readfd, t_part *parts);

//protected functions:
void	protected_pipe(int fd[2]);
int		protected_fork(void);
void	protected_dup2s(int writefd, int readfd);
char	**protected_split(char *to_split, char delimiter);

//libft functions:
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void	*b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
int	ft_putnbr_fd(int n, int fd);

#endif
