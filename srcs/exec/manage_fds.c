/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:58:33 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/14 11:25:47 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_fds(t_fd *fds)
{
	fds->pipe[0] = -2;
	fds->pipe[1] = -2;
	fds->redirection[0] = -2;
	fds->redirection[1] = -2;
	fds->out = -2;
}

void	set_fds(t_fd *fds)
{
	if (fds->pipe[1] != -2)
		fds->out = fds->pipe[1];
	if (fds->redirection[IN] != -2)
	{
		if (fds->in != -2)
			close(fds->in);
		fds->in = fds->redirection[IN];
	}
	if (fds->redirection[OUT] != -2)
	{
		if (fds->pipe[1] != -2)
			close(fds->pipe[1]);
		fds->out = fds->redirection[OUT];
	}
}
