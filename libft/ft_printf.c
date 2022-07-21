/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:17:19 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:02:42 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_flag(const char *fmt, t_info *ret)
{
	if (fmt[ret->i] == '#')
		ret->flag = '#';
	if (fmt[ret->i] == ' ')
	{
		ret->flag = ' ';
		while (fmt[ret->i] == ' ')
			ret->i++;
		ret->i--;
	}
	if (fmt[ret->i] == '+')
	{
		ret->flag = '+';
		while (fmt[ret->i] == '+')
			ret->i++;
		ret->i--;
	}
	return (0);
}

static int	ft_select_conv(const char *fmt, va_list args, t_info *ret)
{
	if (fmt[ret->i] == '#' || fmt[ret->i] == ' ' || fmt[ret->i] == '+')
	{
		ft_set_flag(fmt, ret);
		ret->i++;
	}
	if (fmt[ret->i] == 'c')
		ft_conv_c(args, ret);
	if (fmt[ret->i] == 'd' || fmt[ret->i] == 'i')
		ft_conv_di(args, ret);
	if (fmt[ret->i] == 'u')
		ft_conv_u(args, ret);
	if (fmt[ret->i] == 's')
		ft_conv_s(args, ret);
	if (fmt[ret->i] == 'x' || fmt[ret->i] == 'X')
		ft_conv_x(args, ret, fmt[ret->i]);
	if (fmt[ret->i] == 'p')
		ft_conv_p(args, ret);
	if (fmt[ret->i] == '%')
	{
		ft_putchar_fd('%', 1);
		ret->ret++;
	}
	return (ret->ret);
}

int	ft_printf(const char *fmt, ...)
{
	t_info	ret;
	va_list	args;

	va_start(args, fmt);
	ret.i = 0;
	ret.ret = 0;
	ret.flag = 0;
	while (fmt[ret.i] != '\0')
	{
		if (fmt[ret.i] == '%')
		{
			ret.i++;
			ft_select_conv(fmt, args, &ret);
		}
		else
		{
			ft_putchar_fd(fmt[ret.i], 1);
			ret.ret++;
		}
		ret.i++;
	}
	va_end(args);
	return (ret.ret);
}
