/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:10:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/11 09:59:27 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include <stdio.h> //welke van deze includes hebben we nog nodig?? Even checken
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	check_str(char *str)
{
	if (str != NULL && str[0])
	{
		add_history(str);
		if (ft_isemptyline(str) == 0)
			return 0;
		if (check_double_red(str) < 0)
			return 0;
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
		sigaction(SIGINT, &sa, NULL);
		str = readline("mickeyshell> ");
		if (str == NULL) //which means EOF is encountered (that happens when ctrl-D is pressed)
		{
			printf("exit\n");
			sigaction(SIGQUIT, &sa, NULL);
			return (0);
		}
		if (check_str(str) == 0)
			return (0);
		free (str);
	}
	return (0); //Hier exitcode invullen?
}