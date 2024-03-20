/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:58:33 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/20 15:07:03 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fds(t_fd *fds)
{
	fds->pipe[IN] = UNOPENED_FD;
	fds->pipe[OUT] = UNOPENED_FD;
	fds->redir[IN] = UNOPENED_FD;
	fds->redir[OUT] = UNOPENED_FD;
	fds->out = UNOPENED_FD;
}

void	set_fds(t_fd *fds)
{
	if (fds->pipe[OUT] != UNOPENED_FD)
		fds->out = fds->pipe[OUT];
	if (fds->redir[IN] != UNOPENED_FD)
	{
		if (fds->in != UNOPENED_FD)
			close(fds->in);
		fds->in = fds->redir[IN];
	}
	if (fds->redir[OUT] != UNOPENED_FD)
	{
		if (fds->pipe[OUT] != UNOPENED_FD)
			close(fds->pipe[OUT]);
		fds->out = fds->redir[OUT];
	}
}
