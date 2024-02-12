/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:58:33 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/12 16:04:16 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_init_fds(t_fd *fds)
{
	fds->pipe[0] = -2;
	fds->pipe[1] = -2;
	fds->redirection[0] = -2;
	fds->redirection[1] = -2;
	fds->out = -2;
}