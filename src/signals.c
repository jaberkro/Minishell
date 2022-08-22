/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 10:24:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 16:26:16 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <signal.h>

void	set_sigs_hd(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler_hd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_info.signal_status = 67;
		write(1, "\n", 1);
	}
}

void	sig_handler_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
