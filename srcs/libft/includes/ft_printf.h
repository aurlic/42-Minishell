/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:51:09 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 16:31:12 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_arg
{
	int		err;
	int		len;
	char	specifier;
}				t_arg;

int		ft_printf(const char *format, ...);
void	handle_char(va_list ap, t_arg *arg);
void	handle_string(va_list ap, t_arg *arg);
void	handle_int(va_list ap, t_arg *arg);
void	handle_uint(va_list ap, t_arg *arg);
void	handle_hex(va_list ap, t_arg *arg);
void	handle_pointer(va_list ap, t_arg *arg);

#endif