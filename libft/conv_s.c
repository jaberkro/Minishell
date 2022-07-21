/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_s.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:26:17 by bsomers       #+#    #+#                 */
/*   Updated: 2022/02/11 12:02:55 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conv_s(va_list args, t_info *ret)
{
	char	*arg_s;

	arg_s = va_arg(args, char *);
	if (arg_s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		ret->ret = ret->ret + 6;
	}
	else
	{
		ret->ret = ret->ret + ft_strlen(arg_s);
		ft_putstr_fd(arg_s, 1);
	}
	return (ret->ret);
}
