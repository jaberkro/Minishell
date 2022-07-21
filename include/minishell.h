/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/21 15:35:30 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

/*
	t_part stores information about one part of the user input seperated by pipes
	@in contains the name of the inputfile. 
	@cmd contains the command to be executed. 
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

char *readline (const char *prompt);

#endif
