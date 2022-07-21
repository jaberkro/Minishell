/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_di.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:30:43 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:03:04 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conv_di(va_list args, t_info *ret)
{
	int		arg;
	char	*arg_s;

	arg = va_arg(args, int);
	arg_s = ft_itoa(arg);
	if (ret->flag == '+' && arg >= 0)
	{	
		ft_putchar_fd('+', 1);
		ret->ret++;
		ret->flag = 0;
	}
	else if (ret->flag == ' ' && arg >= 0)
	{	
		ft_putchar_fd(' ', 1);
		ret->ret++;
		ret->flag = 0;
	}
	ret->ret = ret->ret + ft_strlen(arg_s);
	free(arg_s);
	ft_putnbr_fd(arg, 1);
	return (ret->ret);
}
