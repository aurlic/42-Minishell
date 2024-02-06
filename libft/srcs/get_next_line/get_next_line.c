/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:50:40 by aurlic            #+#    #+#             */
/*   Updated: 2023/11/29 15:36:18 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static void	*ret_alloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	i;

	if (size && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(unsigned char *)(arr + i) = '\0';
		i++;
	}
	return (arr);
}

static int	find_newline(char *buf, int *nl_index)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			*nl_index = i + 1;
			return (1);
		}
		i++;
	}
	*nl_index = i;
	return (0);
}

static void	init_struct(t_gnl *line, char *buf)
{
	char	*tmp;

	tmp = ret_alloc(1, sizeof(char));
	line->ret = tmp;
	line->len = 1;
	line->nli = 0;
	line->nl_ret = find_newline(buf, &line->nli);
	line->ret = ft_strnjoin(line->ret, buf, line->nli);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {0};
	t_gnl		line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	init_struct(&line, buf);
	if (line.nl_ret)
		ft_strlcpy(buf, buf + line.nli, ft_strlen(buf) - line.nli + 1);
	while (line.len && !line.nl_ret)
	{
		line.len = read(fd, buf, BUFFER_SIZE);
		if (line.len < 0)
			return (free(line.ret), NULL);
		buf[line.len] = 0;
		if (find_newline(buf, &line.nli) || line.len != BUFFER_SIZE)
		{
			line.ret = ft_strnjoin(line.ret, buf, line.nli);
			ft_memmove(buf, buf + line.nli, line.len - line.nli + 1);
			break ;
		}
		line.ret = ft_strnjoin(line.ret, buf, BUFFER_SIZE);
	}
	if (*line.ret == 0)
		return (free(line.ret), NULL);
	return (line.ret);
}
