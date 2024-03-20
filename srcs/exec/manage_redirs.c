/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:42:36 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 09:53:18 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_input(t_lex *redirs, int token, int fd)
{
	if (fd != UNOPENED_FD)
		close (fd);
	if (token == LOWER)
	{
		fd = open(redirs->word, O_RDONLY);
		if (fd == -1)
			return (perror(redirs->word), g_return = 1, fd);
	}
	else if (token == D_LOWER)
		fd = run_here_doc(redirs, fd);
	ft_printf("fd_here_doc : %d\n", fd);
	return (fd);
}

static int	handle_output(t_lex *redirs, int token, int fd)
{
	if (fd != UNOPENED_FD)
		close (fd);
	if (token == GREATER)
	{
		fd = open(redirs->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(redirs->word), g_return = 1, fd);
	}
	else if (token == D_GREATER)
	{
		fd = open(redirs->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(redirs->word), g_return = 1, fd);
	}
	return (fd);
}

void	open_redirs(t_cmds *cmds, int *fd_in, int *fd_out)
{
	t_lex	*redirs;

	redirs = cmds->redirection;
	while (redirs)
	{
		if (redirs->token == D_LOWER || redirs->token == LOWER)
			*fd_in = handle_input(redirs, redirs->token, *fd_in);
		else if (redirs->token == D_GREATER || redirs->token == GREATER)
			*fd_out = handle_output(redirs, redirs->token, *fd_out);
		if (*fd_in == -1 || *fd_out == -1)
			break ;
		redirs = redirs->next;
	}

}
