/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:19:35 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/26 16:54:43 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_prompt(t_shell *shell)
{
	char		*str;
	static char	*prompt;

	(void)shell;
	if (!prompt)
		prompt = PROMPT_MESSAGE;
	str = readline(prompt);
	if (ft_strictcmp(str, "xxx"))
		prompt = PROMPT_MESSAGE_HIDDEN;
	else if (ft_strictcmp(str, "jeanmi"))
		prompt = PROMPT_MESSAGE;
	if (!str)
	{
		// free_shell(shell);
		exit(g_return);
	}
	return (str);
}
