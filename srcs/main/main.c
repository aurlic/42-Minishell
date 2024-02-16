/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/16 10:08:15 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_return = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*str;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	while (1)
	{
		handle_signals(0);
		str = read_prompt(&shell);
		// ft_printf("la string est bien la : %s\n", str);
		lexer(&shell, str);
	}
}



// while (str)
// {
//   j = 0;
//   tant que jai un escape
//     javance
  
//   si open est diff de 0 -> fonction qui va check le mot qui est entre les deux sep qui renvoie j(proto de fonctio :str, i, sep)
//   tant que jai qqch qui n'est ni un quote ni un token ni un espace et que open est 0 et que str existe
//     j avance pour compter la taille du mot

//   si je tombe sur un SEP, je dup le mot depuis I, sur J caracteres (NOUVEAU MAILLON PUIS JAVANCE)

//   je check si mon sep est token,
//     si oui je flag et nouveau maillon
//     si non javance de 1 et je flag open en fonction du sep

//   puis javance i de j (i +=j)
  
// }