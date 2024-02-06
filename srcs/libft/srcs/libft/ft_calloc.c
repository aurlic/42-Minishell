/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:36:53 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:45:55 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
	Another way of checking the overflow would be to use this equation :

		int	x;

		x = nmemb * size_t
		if (size && x / size != nmemb)
			return (NULL);
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (size && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, nmemb * size);
	return (arr);
}
