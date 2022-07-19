/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 15:26:56 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/19 15:47:43 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	t_part stores information about one part of the user input
	@str contains one part of the input sentence. 
	@ls contains the left border sign of this part.
	@rs contains the right border sign of this part.
	Possible borders: | < > [ ] 0
*/
typedef struct s_part
{
	char	*str;
	char	lb;
	char	rb;
}	t_part;

#endif
