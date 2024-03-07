/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:34:08 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/07 14:16:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_matrix_safe(char **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		printf("free tab = %s\n", matrix[i]);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
