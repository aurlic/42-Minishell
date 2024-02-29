/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strictncmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:33 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/29 14:37:35 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strictncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	printf("s1:[%s]\ns2:[%s]\n", s1, s2);
	while ((s1[i] && s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (i != n)
		return (-1);
	return (0);
}

// int ft_strictncmp(const char *s1, const char *s2, int n)
// {
//     if (!s1 || !s2)
//         return 1;

//     int i = 0;
//     while (s1[i] && s2[i] && i < n)
//     {
//         if (s1[i] != s2[i])
//             return 1;
//         i++;
//     }

//     if (i == n && s1[i] != '\0')
//         return 1;
//     else
//         return 0;
// }