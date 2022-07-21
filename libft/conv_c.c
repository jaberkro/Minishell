/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_c.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:23:08 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:03:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conv_c(va_list args, t_info *ret)
{
	int	arg;

	arg = va_arg(args, int);
	ret->ret++;
	ft_putchar_fd(arg, 1);
	return (ret->ret);
}
