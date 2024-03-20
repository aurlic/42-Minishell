/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:19:35 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 15:42:09 by traccurt         ###   ########.fr       */
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
	if (!str)
		exit_shell(shell, "exit", 1);
	if (ft_strictcmp(str, "xxx"))
		prompt = PROMPT_X;
	else if (ft_strictcmp(str, "kiwi"))
		prompt = PROMPT_K;
	else if (ft_strictcmp(str, "celine"))
		prompt = PROMPT_D;
	else if (ft_strictcmp(str, "jackson"))
		prompt = PROMPT_J;
	else if (ft_strictcmp(str, "voyage"))
		prompt = PROMPT_R;
	else if (ft_strictcmp(str, "jeanmi"))
		prompt = PROMPT;
	add_history(str);
	return (str);
}
