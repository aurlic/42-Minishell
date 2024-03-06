/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:08:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/06 14:49:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	real_len;
	char	*str;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	real_len = ft_strlen(s) - start;
	if (real_len < len)
		len = real_len;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[(size_t)start + i];
	str[i] = '\0';
	return (str);
}
