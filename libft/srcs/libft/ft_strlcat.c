/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:04:15 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:45:05 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
	Removed :
				if (dst)
					lendest = ft_strlen(dst);
				if (src)
					lensrc = ft_strlen(src);
	to match real functions behaviour which segfaults when
	NULL parameter is sent.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	if (!dst && size == 0)
		return (0);
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = lendest;
	j = 0;
	if (size <= lendest)
		return (size + lensrc);
	while (src[j] && i + 1 < size)
		dst[i++] = src[j++];
	dst[i] = '\0';
	if (size < lendest)
		return (lensrc + size);
	return (lendest + lensrc);
}
