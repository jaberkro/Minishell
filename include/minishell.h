/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/20 10:33:05 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>

char	**g_env_variables;

/*
	t_part stores information about one part of the user input
	@str contains one part of the input sentence. 
	@ls contains the left border sign of this part.
	@rs contains the right border sign of this part.
	Possible borders: | < > [ ] 0
*/
typedef struct s_part
{
	char	*str;
	char	lb;
	char	rb;
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

#endif
