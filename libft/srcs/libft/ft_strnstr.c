/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:10:59 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:44:05 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
	Removed :
				if (!big)
					return (NULL);
	to match real functions behaviour which segfaults when
	NULL parameter is sent.
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*lit;
	size_t	i;
	size_t	j;

	if (!big && len == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	b = (char *)big;
	lit = (char *)little;
	i = 0;
	j = 0;
	while (b[i] && i < len)
	{
		j = 0;
		while (lit[j] && b[i + j] && lit[j] == b[i + j] && (i + j) < len)
			j++;
		if (!lit[j])
			return (&b[i]);
		i++;
	}
	return (NULL);
}
