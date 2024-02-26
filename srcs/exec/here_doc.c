/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:31 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/26 15:35:57 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_oget_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

void	run_here_doc(t_shell *shell, t_lex *lex, int *fd)
{
	int		fd_tmp;
	char	*file_name;
	char	*line;

	file_name = ft_strdup("a");
	while (access(file_name, F_OK) == 0)
		file_name = ft_strjoinfree(file_name, "a");
	fd_tmp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd[IN] = open(file_name, O_RDONLY);
	unlink(file_name);
	while (ft_printf("here_doc> ") && ft_oget_next_line(0, &line))
	{
		if (!ft_strncmp(lex->next->word, line, ft_strlen(lex->next->word)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	(free(file_name), free(line));
}

int	manage_here_doc(t_shell *shell, t_cmds *cmds, int *fd)
{
	int		flag;
	t_lex	*tmp;

	flag = -2;
	tmp = cmds->redirection;
	while (tmp)
	{
		if (tmp->token == D_LOWER)
			(run_here_doc(shell, tmp, fd), flag = -3);
		tmp = tmp->next;
	}
	return (flag);
}
