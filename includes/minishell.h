/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:39:53 by traccurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/12 14:31:59 by traccurt         ###   ########.fr       */
=======
/*   Updated: 2024/02/12 14:34:58 by aurlic           ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
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

typedef struct	s_shell
{
	t_env	*env;
	t_path	*path;
	t_cmds	*cmds;
}				t_shell;

#endif