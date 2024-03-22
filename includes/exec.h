/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:26:30 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/22 10:31:48 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"
# include "../srcs/libft/includes/libft.h"

# define IN 0
# define OUT 1
# define UNOPENED_FD -2

typedef struct s_fd
{
	int	pipe[2];
	int	redir[2];
	int	in;
	int	out;
}		t_fd;

/* exec_cmds_utils.c */
void	is_directory(t_shell *shell, t_cmds *cmds, t_fd *fds);
/* exec_cmds.c */
char	*run_cmds(t_shell *shell, t_cmds *cmds, t_fd *fds);
void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds);
/* exec.c */
void	run_exec(t_shell *shell);
void	close_parent(t_fd *fds);
/* here_doc.c */
int		run_here_doc(t_shell *shell, t_lex *lex, int fd);
/* manage_fds.c */
void	init_fds(t_fd *fds);
void	set_fds(t_fd *fds);
/* manage_redirs.c */
void	open_redirs(t_shell *shell, t_cmds *cmds, int *fd_in, int *fd_out);

#endif