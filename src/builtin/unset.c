/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 15:28:44 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/08/15 18:33:44 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //weghalen

int	execute_unset(char **commands, int max)
{
	(void)max;
	printf("unsetting %s...\n", commands[1]);
	return (0);
}
