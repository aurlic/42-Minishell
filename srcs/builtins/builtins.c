/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:46 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/25 15:44:42 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_fds(t_shell *shell, t_fd *fds)
{
	if (fds->in != UNOPENED_FD)
		close(fds->in);
	if (fds->out == UNOPENED_FD)
		fds->out = dup(STDOUT_FILENO);
	if (fds->out == -1)
		(close_all_fds(fds), exit_shell(shell, "dup2", 1));
}

void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag)
{
	builtins_fds(shell, fds);
	if (cmds->is_builtin == ECHO)
		echo_builtin(cmds, fds->out);
	if (cmds->is_builtin == CD)
		cd_builtin(shell, cmds);
	if (cmds->is_builtin == PWD)
		pwd_builtin(shell, cmds, fds->out);
	if (cmds->is_builtin == ENV)
		env_builtin(shell, fds->out);
	if (cmds->is_builtin == EXIT)
		exit_builtin(shell, cmds, fds, flag);
	if (cmds->is_builtin == UNSET)
		unset_builtin(shell, cmds);
	if (cmds->is_builtin == EXPORT)
		export_builtin(shell, cmds, fds);
}

char	**cut_builtin(t_shell *shell, char **tab, int i, int j)
{
	char	**expand_tab;
	char	**new_tab;
	int		size;

	size = 0;
	expand_tab = ft_split(tab[0], ' ');
	size = split_count(tab);
	new_tab = ft_calloc(size + 2, sizeof(char *));
	new_tab[0] = ft_strdup(expand_tab[0]);
	if (expand_tab[1])
		new_tab[i++] = ft_strdup(expand_tab[1]);
	else if (tab[j])
		new_tab[i] = ft_strdup(tab[j++]);
	if (!new_tab)
		exit_shell(shell, "builtin malloc", 1);
	while (expand_tab[i])
		new_tab[1] = ft_strjoin_free(new_tab[1], expand_tab[i++]);
	while (tab[j])
	{
		new_tab[j] = ft_strdup(tab[j]);
		j++;
	}
	new_tab[j + 1] = NULL;
	(free_matrix_safe(expand_tab), free_matrix_safe(tab));
	return (new_tab);
}

static int	find_builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 4) && (str[4] <= 32))
		return (1);
	if (!ft_strncmp(str, "cd", 2) && (str[2] <= 32))
		return (1);
	if (!ft_strncmp(str, "pwd", 3) && (str[3] <= 32))
		return (1);
	if (!ft_strncmp(str, "export", 6) && (str[6] <= 32))
		return (1);
	if (!ft_strncmp(str, "unset", 5) && (str[5] <= 32))
		return (1);
	if (!ft_strncmp(str, "env", 3) && (str[3] <= 32))
		return (1);
	if (!ft_strncmp(str, "exit", 4) && (str[4] <= 32))
		return (1);
	return (0);
}

void	parse_builtins(t_shell *shell)
{
	t_cmds	*tmp;
	int		i;
	int		j;

	i = 1;
	j = 1;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp && find_builtin(tmp->tab[0]))
			tmp->tab = cut_builtin(shell, tmp->tab, i, j);
		if (is_builtin(tmp->tab[0]))
			tmp->is_builtin = is_builtin(tmp->tab[0]);
		tmp = tmp->next;
	}
}
