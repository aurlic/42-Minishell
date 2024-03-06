/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:39:53 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:14 by marvin           ###   ########.fr       */
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
void	free_cmds(t_cmds *cmds);

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
void	store_new_word(t_shell *shell, t_lex **lex, char *str, int i, int j);

/*
======================= parser ======================
*/
/*                    parser.c                      */
void	parser(t_shell *shell, t_lex *lex);
/*                    check_syntax.c                */
int		count_commands(t_lex *lex);
int		count_redir(t_lex *cmd_start, t_lex *lex);
int		check_syntax(t_lex *lex);
void	redesign_words(t_lex *lex);
/*                    process_command.c             */
t_cmds	*process_command(t_shell *shell, t_lex *lex, t_lex *cmd_start, t_cmds *new_cmd);
/*                    process_command_utils.c       */
void	new_redi(t_shell *shell, t_lex **head, t_lex **tmp, t_lex *cmd_start, t_cmds *new_cmd);
/*                    dollar_handler.c              */
void	find_dollar(t_cmds *cmds, t_env *env, int i, int j);

/*
======================= builtins ======================
*/
/*                    builtins.c                      */
int		is_builtin(char *str);

#endif