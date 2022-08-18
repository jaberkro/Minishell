/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/18 12:16:37 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>

typedef struct s_env_info
{
	char	**env;
	char	**paths;
	int		return_value;
	pid_t	*pids;
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

typedef struct s_builtin
{
	char	*key;
	int		(*func)(char **commands, int max);
}				t_builtin;

//global function
void	init_global(char **env);

//env functions
char	*get_env_variable(char *to_find);
void	set_env_variable(char *variable);
char	**get_paths(void);
char	**copy_array(char **to_copy);
void	unset_env_variable(char *variable);

// builtin functions
int		find_builtin_function(char **commands, int max);
int		execute_cd(char **commands, int max);
int		execute_echo(char **commands, int max);
int		execute_env(char **commands, int max);
int		execute_exit(char **commands, int max);
int		execute_export(char **commands, int max);
int		execute_pwd(char **commands, int max);
int		execute_unset(char **commands, int max);

//executer functions
int		executer(int i, int max, int readfd, t_part_split *parts);
char	*command_in_paths(char	*argument, char **paths);
void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);
void	write_exit_argument(char *argument, char *message, int exit_code);
int		error_return(char *message, int exit_code);

//protected functions
void	protected_pipe(int fd[2]);
int		protected_fork(void);
void	protected_dup2s(int readfd, int writefd);
char	**protected_split(char *to_split, char delimiter);
char	*protected_split_grep_one(char *to_split, char delimiter, int index);

//parser functions
int		calc_len_word_after(char *str, int i);
int		ft_isemptyline(char *str);
char	ft_isred(char c);
char	**ft_split_pipes(char const *s, char c);
char	*readline(const char *prompt);
char	*set_space(char *str, int start, int len);
char	*handle_here_doc(char *str, int i, int heredocs);
void	delete_temp_heredoc_files(int heredocs);
char	*remove_quotes(char *str);
char	*remove_double_quotes(char *str);
int		set_quote_flag(int q, char c);
int		is_double_red(char *str);
void	exec_minishell(char *input);
void	free_struct(t_part parts);
void	clean_up(int heredocs, char **input_split, t_part_split *part_split, int count);
int	set_fill_split_parts(char **input_split, int count_pipe, t_part_split *part_split, int heredocs);
int	count_pipes(char *str);
char	*set_value(char *to_set, char *str, int start, int len);
char	*from_heredoc(t_part *part, char *str, int heredocs, int *i_ptr);
char	*from_infile(t_part *part, char *str, int *q_ptr, int *i_ptr);
char	*to_outfile_app(t_part *part, char *str, int *q_ptr, int *i_ptr);
char	*to_outfile(t_part *part, char *str, int *q_ptr, int *i_ptr);

void	sig_handler(int sig);
void	sig_handler_hd(int sig);
void	sig_handler_exec(int sig);
void    suppress_output_terminal(void);


//dollar functions
char	*extend_dollars(char *input);

#endif
