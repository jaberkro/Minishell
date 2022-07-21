/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_Xx.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 19:12:09 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:02:48 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dectohex_low(unsigned int dec, t_info *ret)
{
	if (dec >= 16)
		ft_dectohex_low(dec / 16, ret);
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

int	ft_dectohex_up(unsigned int dec, t_info *ret)
{
	if (dec >= 16)
		ft_dectohex_up(dec / 16, ret);
	dec = dec % 16;
	if (dec >= 10 && dec <= 15)
	{
		if (dec >= 10 && dec <= 15)
		{
			ft_putchar_fd(dec + 55, 1);
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

int	ft_conv_x(va_list args, t_info *ret, char fmt_i)
{
	unsigned int	arg_u;

	arg_u = va_arg(args, unsigned int);
	if (fmt_i == 'x')
	{
		if (ret-> flag == '#' && arg_u != 0)
		{
			ft_putstr_fd("0x", 1);
			ret->ret = ret->ret + 2;
			ret->flag = 0;
		}
		ft_dectohex_low(arg_u, ret);
	}
	if (fmt_i == 'X')
	{
		if (ret-> flag == '#' && arg_u != 0)
		{
			ft_putstr_fd("0X", 1);
			ret->ret = ret->ret + 2;
			ret->flag = 0;
		}
		ft_dectohex_up(arg_u, ret);
	}
	return (ret->ret);
}
