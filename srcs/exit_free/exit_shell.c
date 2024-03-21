/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:14:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 17:22:28 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_token(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
}

void	token_error(int token)
{
	if (token == PIPE)
		exit_token("Syntax error near unexpected token `|'\n");
	if (token == LOWER)
		exit_token("Syntax error near unexpected token `<'\n");
	if (token == D_LOWER)
		exit_token("Syntax error near unexpected token `<<'\n");
	if (token == GREATER)
		exit_token("Syntax error near unexpected token `>'\n");
	if (token == D_GREATER)
		exit_token("Syntax error near unexpected token `>>'\n");
}

void	exit_shell(t_shell *shell, char *error_msg, int flag)
{
	if (ft_strictcmp(error_msg, "exit"))
		ft_printf("exit\n");
	else if (ft_strictcmp(error_msg, "void"))
		;
	else
		perror(error_msg);
	if (flag == 1)
		g_return = 127;
	free_shell(shell);
	exit(g_return);
}
