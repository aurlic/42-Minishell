/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:01:14 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/16 10:34:02 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_countwords(const char *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if ((!i || s[i - 1] == c) && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	word;
	char	**ret;

	if (!s)
		return (NULL);
	ret = ft_calloc((ft_countwords(s, c) + 1), sizeof(*ret));
	word = 0;
	i = 0;
	while (*s && ret)
	{
		i = 1;
		if (*s != c)
		{
			while (s[i] && s[i] != c)
				i++;
			ret[word] = malloc(i + 1);
			if (!ret[word])
				return (free_matrix(ret), NULL);
			ft_strlcpy(ret[word++], s, i + 1);
		}
		s += i;
	}
	return (ret);
}
