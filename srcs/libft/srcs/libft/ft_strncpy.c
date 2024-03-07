/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:20:46 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/06 16:51:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_fstrncpy(char *dest, char *src, unsigned int n)
{
	char	*tmp;
	char	*result;

	tmp = dest;
	result = ft_strncpy(dest, src, n);
	return (free(tmp), result);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
