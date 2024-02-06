/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:49:24 by aurlic            #+#    #+#             */
/*   Updated: 2023/12/06 15:56:47 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_putandcountnbr(long long nbr, t_arg *arg)
{
	if (nbr < 0)
	{
		arg->len++;
		ft_putchar_fd('-', 1);
		nbr = nbr * -1;
	}
	if (nbr >= 0 && nbr <= 9)
	{
		arg->len++;
		ft_putchar_fd(nbr + '0', 1);
	}
	if (nbr > 9)
	{
		ft_putandcountnbr(nbr / 10, arg);
		ft_putandcountnbr(nbr % 10, arg);
	}
}

void	handle_char(va_list ap, t_arg *arg)
{
	char	c;

	c = va_arg(ap, int);
	ft_putchar_fd(c, 1);
	arg->len++;
}

void	handle_string(va_list ap, t_arg *arg)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		arg->len += 6;
		return ;
	}
	ft_putstr_fd(str, 1);
	arg->len += ft_strlen(str);
}

void	handle_int(va_list ap, t_arg *arg)
{
	long long	i;

	i = va_arg(ap, int);
	ft_putandcountnbr(i, arg);
}

void	handle_uint(va_list ap, t_arg *arg)
{
	unsigned long	i;

	i = va_arg(ap, unsigned int);
	ft_putandcountnbr(i, arg);
}
