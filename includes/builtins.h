/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:43 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:31:52 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

# define ECHO 2001
# define CD 2002
# define PWD 2003
# define EXPORT 2004
# define UNSET 2005
# define ENV 2006
# define EXIT 2007

/* builtins.c */
int		is_builtin(char *str);
void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag);
void	close_all_fds(t_fd *fds);
/* cd.c */
void	cd_builtin(t_shell *shell, t_cmds *cmds);
/* echo.c */
void	echo_builtin(t_cmds *cmds, int fd_out);
/* env.c */
void	env_builtin(t_shell *shell, int fd_out);
/* exit.c */
void	exit_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag);
/* export_utils.c */
void	no_arg(t_shell *shell, t_fd *fds);
/* export.c */
void	export_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds);
/* pwd */
void	pwd_builtin(t_shell *shell, t_cmds *cmds, int fd_out);
/* unset.c */
void	unset_builtin(t_shell *shell, t_cmds *cmds);

#endif