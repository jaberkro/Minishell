/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/05 15:44:32 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env_info
{
	char	**env;
	char	**paths;
	int		return_value;
}	t_env_info;

t_env_info	g_info;

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
	char	*out_r;
}	t_part;

typedef struct s_part_split
{
	char	**in;
	char	**cmd;
	char	**out;
	char	*out_r;
}	t_part_split;

//global functions
void	init_global(char **env);
char	*get_env_variable(char *to_find);
int		set_env_variable(char *variable);
char	**get_paths(void);

// builtin functions
void	execute_pwd(void);
void	find_builtin_function(char *command, int parts);

//executer functions
void	error_exit(char *message, int exit_code);
int		executer(int i, int max, int readfd, t_part_split *parts);
char	*command_in_paths(char	*argument, char **paths);
void	write_exit(char *message, int exit_code);
void	write_exit_argument(char *argument, char *message, int exit_code);

//protected functions
void	protected_pipe(int fd[2]);
int		protected_fork(void);
void	protected_dup2s(int readfd, int writefd);
char	**protected_split(char *to_split, char delimiter);

//parser functions
int		calc_len_word_before(char *str, int i);
int		calc_len_word_after(char *str, int i);
int		ft_isemptyline(char *str);
char	ft_isred(char c);
char	**ft_split_pipes(char const *s, char c);
char	*readline(const char *prompt);
char	*set_space(char *str, int start, int len);
char	*handle_here_doc(char *str, int i, int heredocs);
char	*remove_quotes(char *str);
int	set_quote_flag(int q, char c);

//dollar functions
char	*extend_dollars(char *input);

#endif
