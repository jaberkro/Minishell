/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:10:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/19 15:06:03 by bsomers       ########   odam.nl         */
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
		exec_minishell(str);
	}
	return (1);
}

int	main()
{
	extern char **environ;
	char *str;
	struct sigaction	sa;

	rl_catch_signals = 0; //readline now doesn't install default signal handlers :)
	sa.sa_handler = &sig_handler;
	init_global(environ);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGUSR1, SIG_IGN);
		sigaction(SIGINT, &sa, NULL);
	    // g_info.sigflag = 0;
		str = readline("mickeyshell> ");
		if (str == NULL) //which means EOF is encountered (that happens when ctrl-D is pressed)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		check_str(str);
		free (str);
	}
	return (0); //Hier exitcode invullen?
}