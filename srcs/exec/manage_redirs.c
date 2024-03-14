/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:42:36 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 18:43:18 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input(t_shell *shell, t_lex *redirs, int token, int fd)
{
	if (fd != UNOPENED_FD)
		close (fd);
	if (token == LOWER)
	{
		fd = open(redirs->word, O_RDONLY);
		if (fd == -1)
			return(perror(redirs->word), g_return = 1, fd);
	}
	else if (token == D_LOWER)
		fd = run_here_doc(shell, redirs, fd);
	return (fd);
}

int	handle_output(t_shell *shell, t_lex *redirs, int token, int fd)
{
	if (fd != UNOPENED_FD)
		close (fd);
	if (token == GREATER)
	{
		fd = open(redirs->word, 0)
	}
}