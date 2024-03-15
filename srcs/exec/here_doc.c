/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:31 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/15 09:49:13 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

int	run_here_doc(t_shell *shell, t_lex *redirs, int fd)
{
	int		fd_tmp;
	char	*file_name;
	char	*line;

	(void)shell;
	file_name = ft_strdup("/tmp/.a");
	while (access(file_name, F_OK) == 0)
		file_name = ft_strjoin_free(file_name, "a");
	fd_tmp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd = open(file_name, O_RDONLY);
	unlink(file_name);
	while (ft_printf("here_doc> ") && read_next_line(0, &line))
	{
		if (!ft_strncmp(redirs->word, line, ft_strlen(redirs->word)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	(free(file_name), free(line));
	return (fd);
}
