/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specifier2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:04:21 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:52:45 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_putptr(unsigned long int nbr, char *base, t_arg *arg)
{
	unsigned long int	base_len;

	base_len = 0;
	while (base[base_len] != '\0')
		base_len++;
	if (nbr < base_len)
	{
		arg->len++;
		ft_putchar_fd(base[nbr], 1);
	}
	else
	{
		ft_putptr(nbr / base_len, base, arg);
		ft_putptr(nbr % base_len, base, arg);
	}
}

static void	ft_putnbr_base(long nb, char *base, t_arg *arg)
{
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (nb >= 0 && nb < base_len)
	{
		arg->len++;
		ft_putchar_fd(base[nb], 1);
	}
	if (nb >= base_len)
	{
		ft_putnbr_base(nb / base_len, base, arg);
		ft_putnbr_base(nb % base_len, base, arg);
	}
}

void	handle_hex(va_list ap, t_arg *arg)
{
	unsigned int	i;

	i = va_arg(ap, unsigned int);
	if (arg->specifier == 'x')
		ft_putnbr_base(i, "0123456789abcdef", arg);
	else if (arg->specifier == 'X')
		ft_putnbr_base(i, "0123456789ABCDEF", arg);
}

void	handle_pointer(va_list ap, t_arg *arg)
{
	void	*ptr;

	ptr = va_arg(ap, void *);
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		arg->len += 5;
		return ;
	}
	ft_putstr_fd("0x", 1);
	arg->len += 2;
	ft_putptr((unsigned long int)ptr, "0123456789abcdef", arg);
}
