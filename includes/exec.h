/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:26:30 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/13 16:50:18 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define IN 0
# define OUT 1

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

typedef struct s_fd
{
	int pipe[2];
	int redirection[2];
	int in;
	int out;
}t_fd;

/*init_fds.c*/
void ft_init_fds(t_fd *fds);

/*here_doc*/
//void	run_here_doc(t_shell *shell, t_lex *lex, t_fd *fds);

#endif