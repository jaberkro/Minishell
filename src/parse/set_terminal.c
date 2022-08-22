/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_terminal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:18:28 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/22 17:42:51 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <termios.h>

/**
 * @brief Set the terminal settings to show or hide ˆC and ˆ\ with ECHOCTL flag
 * 
 * @param flag tells whether ECHOCTL is currently on or off
 */
void	set_output_terminal(int flag)
{
	struct termios	new_settings;

	if (flag == 0)
	{
		if (tcgetattr(0, &new_settings))
			error_exit("tcgetattr", 1);
		new_settings.c_lflag &= ~ECHOCTL;
		if (tcsetattr(0, 0, &new_settings))
			error_exit("tcsetattr", 1);
	}
	else
	{
		if (tcgetattr(0, &new_settings))
			error_exit("tcgetattr", 1);
		new_settings.c_lflag |= ECHOCTL;
		if (tcsetattr(0, 0, &new_settings))
			error_exit("tcsetattr", 1);
	}
}
