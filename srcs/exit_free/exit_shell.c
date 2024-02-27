/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:14:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/27 15:16:04 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	exit_shell(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}
