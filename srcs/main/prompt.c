/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:19:35 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/15 14:29:21 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_prompt(t_shell *shell)
{
	char	*str;

	(void)shell;
	str = readline(PROMPT_MESSAGE);
	if (!str)
	{
		// free_shell(shell);
		exit(g_return);
	}
	return (str);
}