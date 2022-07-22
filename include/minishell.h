/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/22 15:38:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stdio.h>

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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

//executer functions
void	error_exit(char *message, int exit_code);
int		executer(int i, int max, int readfd, t_part *parts);
char	*command_in_paths(char	*argument, char **paths);
void	write_exit(char *message, int exit_code);
void	write_exit_argument(char *argument, char *message, int exit_code);

//protected functions
void	protected_pipe(int fd[2]);
int		protected_fork(void);
void	protected_dup2s(int writefd, int readfd);
char	**protected_split(char *to_split, char delimiter);

//parser functions
int		calc_len_word_before(char *str, int i);
int		calc_len_word_after(char *str, int i);
char	*readline(const char *prompt);
char	*set_space(char *str, int start, int len);

#endif
