/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:44:28 by eates             #+#    #+#             */
/*   Updated: 2024/01/22 19:20:53 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

int	pre_create_path(t_ms *ms, char **path)
{
	if (ms->cmd->value[0] == '.' || ms->cmd->value[0] == '/')
	{
		*path = ft_strdup(ms->cmd->value);
		if_error_frees(ms, *path, 1);
		if (access(*path, F_OK))
		{
			write_error("minishell: ", *path, ": No such file or directory");
			free(*path);
			frees(ms, 127);
		}
		return (1);
	}
	return (0);
}

char	*create_path(t_ms *ms, char *path, int i)
{
	char	**paths;

	if (pre_create_path(ms, &path))
		return (path);
	path = get_env(ms, "PATH");
	if (!path)
		return (write_error("minishell: ", ms->cmd->value,
				": No such file or directory"), frees(ms, 127), NULL);
	paths = ft_split(path, ':');
	ft_free((void **)&path, 0);
	if_error_frees(ms, paths, 1);
	while (paths[++i])
	{
		ms->tmp1 = ft_strjoin(paths[i], "/");
		if_error_frees(ms, ms->tmp1, 1);
		path = ft_strjoin(ms->tmp1, ms->cmd->value);
		if_error_frees(ms, path, 1);
		if (!access(path, F_OK))
			return (ft_free_malloc(paths),
				ft_free((void **)&ms->tmp1, 0), path);
		ft_free((void **)&ms->tmp1, 0);
		ft_free((void **)&path, 0);
	}
	return (ft_free_malloc(paths), write_error("minishell: ", ms->cmd->value,
			": command not found"), frees(ms, 127), NULL);
}
