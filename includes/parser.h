/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:10:57 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:36:49 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

# define PIPE 1001
# define LOWER 1002
# define D_LOWER 1003
# define GREATER 1004
# define D_GREATER 1005

typedef struct s_cmds
{
	char			**tab;
	int				is_builtin;
	int				pid;
	int				end;
	struct s_lex	*redirection;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}					t_cmds;

/* dollar_handler.c */
void	find_dollar(t_shell *shell, t_cmds *cmds, int i, int j);
/* handle_commands.c */
void	new_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
t_cmds	*create_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
void	parse_cmds_tab(t_shell *shell, int i);
/* handle_redirections.c */
void	set_redir(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
/* parser_syntax.c */
int		check_syntax(t_lex *lex);
void	redesign_words(t_shell *shell, t_lex *lex);
/* parser_utils.c */
int		count_tab_size(t_lex *tmp_lex, t_lex *curr);
/* parser.c */
void	parser(t_shell *shell, t_lex *lex);

#endif
