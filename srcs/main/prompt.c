/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:19:35 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/28 16:42:25 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_prompt(t_shell *shell)
{
	char		*str;
	static char	*prompt;

	(void)shell;
	if (!prompt)
		prompt = PROMPT;
	str = readline(prompt);
	if (ft_strictcmp(str, "xxx"))
		prompt = PROMPT_X;
	else if (ft_strictcmp(str, "jeanmi"))
		prompt = PROMPT;
	if (!str)
	{
		// free_shell(shell);
		exit(g_return);
	}
	return (str);
}
