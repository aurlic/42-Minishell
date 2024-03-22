/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:39:53 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/22 10:34:34 by aurlic           ###   ########.fr       */
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
/* init.c */
void	init_shell(t_shell *shell, char **envp);
/* prompt.c */
char	*read_prompt(t_shell *shell);
/* signals.c */
void	handle_signals(int action);

/*
======================= exit_free ===================
*/
/* exit_shell.c */
void	exit_shell(t_shell *shell, char *error_msg, int flag);
void	token_error(int token);
/* free_shell.c */
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmds(t_cmds **cmds);
void	free_lex(t_lex **lex);
void	free_before_new_loop(t_shell *shell);

#endif
