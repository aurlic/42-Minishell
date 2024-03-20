/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:39:53 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/20 13:32:07 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"
# include "builtins.h"
# include "lexer.h"
# include "env.h"
# include "exec.h"

extern int	g_return;

typedef struct s_shell
{
	t_env	*env;
	t_path	*path;
	t_cmds	*cmds;
}			t_shell;

/*
======================= main =======================
*/
/*                     init.c                       */
void	init_shell(t_shell *shell, char **envp);
/*                    prompt.c                       */
char	*read_prompt(t_shell *shell);
/*                    signals.c                       */
void	handle_signals(int action);

/*
======================= env =======================
*/
/*                   get_env.c                      */
void	get_env(t_shell *shell, char **envp);

/*                    n_env.c                       */
void	handle_no_env(t_shell *shell);

/*
======================= exit_free ===================
*/
/*                    exit_shell.c                  */
void	exit_shell(t_shell *shell, char *error_msg);
void	token_error(int token);
/*                    free_shell.c                  */
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmds(t_cmds **cmds);
void	free_lex(t_lex **lex);
void	free_before_new_loop(t_shell *shell);

/*
======================= lexer =======================
*/
/*                    lexer.c                       */
t_lex	*lexer(t_shell *shell, char *str);
/*                    quotes.c                      */
int		quote_is_goat(char quote);
int		quote_checker(char *str);
int		is_token(char *str, int i);
/*                    store_token_words.c           */
void	store_new_token(t_shell *shell, t_lex **lex, int token);
// void	store_new_word(t_shell *shell, t_lex **lex, char *str, int i, int j);
void	store_new_word(t_shell *shell, t_lex **lex, char *str, int ij[2]);

/*
======================= parser ======================
*/
/*                    parser.c                      */
void	parser(t_shell *shell, t_lex *lex);
/*                    parser_utils.c                */
int		count_tab_size(t_lex *tmp_lex, t_lex *curr);
/*                    handle_commands.c             */
void	new_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
t_cmds	*create_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
void	parse_cmds_tab(t_shell *shell);
/*                    handle_redirections.c             */
void	set_redir(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr);
/*                    dollar_handler.c              */
void	find_dollar(t_cmds *cmds, t_env *env, int i, int j);
/*                    parser_syntax.c               */
int		check_syntax(t_lex *lex);
void	redesign_words(t_shell *shell, t_lex *lex);

/*
======================= exec ==========================
*/
/*                    exec.c                          */
void	run_exec(t_shell *shell);
/*                    manage_redirs.c                 */
void	open_redirs(t_cmds *cmds, int *fd_in, int *fd_out);
/*                    here_doc.c                      */
int		run_here_doc(t_lex *lex, int fd);
/*                    manage_fds.c                      */
void	init_fds(t_fd *fds);
void	set_fds(t_fd *fds);
char	*run_cmds(t_shell *shell, t_cmds *cmds);
void	close_parent(t_fd *fds);
void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds);

/*
======================= builtins ======================
*/
/*                    builtins.c                      */
int		is_builtin(char *str);
void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag);
void	close_before_exit(t_fd *fds);

void 	pwd_builtin(t_shell *shell, int fd_out);
void	env_builtin(t_shell *shell, int fd_out);
void	echo_builtin(t_cmds *cmds, int fd_out);
void	cd_builtin(t_shell *shell, t_cmds *cmds);
void	unset_builtin(t_shell *shell, t_cmds *cmds);
void	exit_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds);

#endif
