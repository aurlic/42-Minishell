/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:19:35 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/14 10:41:17 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_prompt(void)
{
	char	*str;

	str = readline(PROMPT_MESSAGE);
	if (!str)
		exit_shell("readline");
	return (str);
}