/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:55:23 by eates             #+#    #+#             */
/*   Updated: 2023/10/12 14:01:49 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>

void	finish(t_pipex *pipex, int status)
{
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->pipefd)
		free_double_array((void **)pipex->pipefd);
	if (pipex->cmd_paths)
		free_double_array((void **)pipex->cmd_paths);
	if (pipex->cmd && status)
		free(pipex->cmd);
	if (pipex->str && status)
		free_double_array((void **)pipex->str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!string)
		return (0);
	if (!s1 && !s2)
		return (0);
	i = -1;
	while (s1[++i])
		string[i] = s1[i];
	j = -1;
	while (s2[++j])
		string[i + j] = s2[j];
	return (string[i + j] = '\0', string);
}

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize != 0)
	{
		i = -1;
		while (src[++i] != '\0' && i < (dstsize - 1))
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
