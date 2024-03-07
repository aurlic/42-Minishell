/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/07 11:19:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	get_len(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		i;
	long	nb;

	i = 0;
	nb = n;
	len = get_len(nb);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
		i++;
	}
	while (len >= i)
	{
		res[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (res);
}
