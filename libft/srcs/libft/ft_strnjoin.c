/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:37:50 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:44:11 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*joined_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	joined_str = malloc(((s1_len + len) * sizeof(char)) + 1);
	if (!joined_str)
		return (NULL);
	while (i < s1_len)
	{
		joined_str[i] = s1[i];
		i++;
	}
	free(s1);
	while (j < len)
	{
		joined_str[i + j] = s2[j];
		j++;
	}
	joined_str[i + j] = '\0';
	return (joined_str);
}
