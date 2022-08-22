/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:10:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/22 11:30:14 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	check_str(char *str)
{
	if (str != NULL && str[0])
	{
		add_history(str);
		if (ft_isemptyline(str) == 0)
			return (0);
		if (is_double_red(str) < 0)
			return (error_return("wrong use of redirectors\n", 1));
		parse_exec_minishell(str);
	}
	return (1);
}

int	main(void)
{
	extern char			**environ;
	char				*str;
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = &sig_handler;
	init_global(environ);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sa, NULL);
		// sigaction(SIGQUIT, &sa, NULL);
		str = readline("mickeyshell> ");
		if (str == NULL)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		check_str(str);
		free (str);
	}
	return (0);
}
