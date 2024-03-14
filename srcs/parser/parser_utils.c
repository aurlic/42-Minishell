/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:14:41 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 10:15:01 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tab_size(t_lex *tmp_lex, t_lex *curr)
{
	int	i;

	i = 0;
	while (curr != tmp_lex)
	{
		if (curr->skip == 0)
			i++;
		curr = curr->next;
	}
	return (i);
}
