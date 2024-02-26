/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:39:53 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/26 14:22:02 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

typedef struct	s_shell
{
	t_env	*env;
	t_path	*path;
	t_cmds	*cmds;
}				t_shell;

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
======================= error =======================
*/
/*                    error.c                       */
void	exit_shell(char *error_msg);

/*
======================= lexer =======================
*/
/*                    lexer.c                       */
void	lexer(t_shell *shell, char *str);
/*                    quotes.c                      */
int		quote_is_goat(char quote);
int		quote_checker(char *str);
int		is_token(char *str, int i);
/*                    store_token_words.c           */
void	store_new_token(t_lex **lex, int token);
void	store_new_word(t_lex **lex, char *str, int i, int j);

#endif