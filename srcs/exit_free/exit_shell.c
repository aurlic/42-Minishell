/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:14:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 11:46:27 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_token(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
}

void	token_error(int token)
{
	if (token == PIPE)
		exit_token("Syntax error near unexpected token `|'\n");
	if (token == LOWER)
		exit_token("Syntax error near unexpected token `<'\n");
	if (token == D_LOWER)
		exit_token("Syntax error near unexpected token `<<'\n");
	if (token == GREATER)
		exit_token("Syntax error near unexpected token `>'\n");
	if (token == D_GREATER)
		exit_token("Syntax error near unexpected token `>>'\n");
}

void	close_all_fds(t_fd *fds)
{
	if (!(fds->pipe[IN] == UNOPENED_FD) && fds->pipe[IN] >= 0)
		close(fds->pipe[IN]);
	if (!(fds->pipe[OUT] == UNOPENED_FD) && fds->pipe[OUT] >= 0)
		close(fds->pipe[OUT]);
	if (!(fds->redir[IN] == UNOPENED_FD) && fds->redir[IN] >= 0)
		close(fds->redir[IN]);
	if (!(fds->redir[OUT] == UNOPENED_FD) && fds->redir[OUT] >= 0)
		close(fds->redir[OUT]);
	if (!(fds->out == UNOPENED_FD) && fds->out >= 0)
		close(fds->out);
	if (!(fds->in == UNOPENED_FD) && fds->in >= 0)
		close(fds->in);
}

void	exit_shell(t_shell *shell, char *error_msg, int flag)
{
	if (ft_strictcmp(error_msg, "exit"))
		ft_printf("exit\n");
	else if (ft_strictcmp(error_msg, "void"))
		;
	else
		perror(error_msg);
	if (flag == 1)
		g_return = 127;
	free_shell(shell);
	exit(g_return);
}
