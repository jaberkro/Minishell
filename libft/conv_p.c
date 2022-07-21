/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_p.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:14:25 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:02:59 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptohex(unsigned long dec, t_info *ret)
{
	if (dec >= 16)
		ft_ptohex(dec / 16, ret);
	dec = dec % 16;
	if (dec >= 10 && dec <= 15)
	{
		if (dec >= 10 && dec <= 15)
		{
			ft_putchar_fd(dec + 87, 1);
			ret->ret++;
		}
		else
		{
			ft_putchar_fd((dec % 16) + '0', 1);
			ret->ret++;
		}
	}
	else
	{
		ft_putchar_fd((dec % 16) + '0', 1);
		ret->ret++;
	}
	return (ret->ret);
}

int	ft_conv_p(va_list args, t_info *ret)
{
	unsigned long	arg_u;

	arg_u = va_arg(args, unsigned long);
	ft_putstr_fd("0x", 1);
	ret->ret = ret->ret + 2;
	ft_ptohex(arg_u, ret);
	return (ret->ret);
}
