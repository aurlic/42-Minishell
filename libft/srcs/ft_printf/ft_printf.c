/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:58:53 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:52:44 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	convert_specifier(va_list ap, t_arg *arg)
{
	if (arg->specifier == 'c')
		handle_char(ap, arg);
	else if (arg->specifier == 's')
		handle_string(ap, arg);
	else if (arg->specifier == 'p')
		handle_pointer(ap, arg);
	else if (arg->specifier == 'd')
		handle_int(ap, arg);
	else if (arg->specifier == 'i')
		handle_int(ap, arg);
	else if (arg->specifier == 'u')
		handle_uint(ap, arg);
	else if (arg->specifier == 'x')
		handle_hex(ap, arg);
	else if (arg->specifier == 'X')
		handle_hex(ap, arg);
	else if (arg->specifier == '%')
	{
		arg->len++;
		ft_putchar_fd('%', 1);
	}
}

static void	check_specifier(char spec, t_arg *arg)
{
	if (spec == 'c' || spec == 's' || spec == 'p' || spec == 'd' || spec == 'i'
		|| spec == 'u' || spec == 'x' || spec == 'X' || spec == '%')
		arg->specifier = spec;
	else
		arg->err = -1;
}

static void	check_args(const char *format, va_list ap, t_arg *arg)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			arg->len++;
		}
		else
		{
			i++;
			check_specifier(format[i], arg);
			if (arg->err == -1)
				return ;
			convert_specifier(ap, arg);
		}
		i++;
	}
}

static void	init_struct(t_arg *arg)
{
	arg->len = 0;
	arg->err = 0;
	arg->specifier = 0;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_arg	arg;

	if (!format)
		return (-1);
	init_struct(&arg);
	va_start(ap, format);
	check_args(format, ap, &arg);
	va_end(ap);
	if (arg.err == -1)
		return (-1);
	return (arg.len);
}
