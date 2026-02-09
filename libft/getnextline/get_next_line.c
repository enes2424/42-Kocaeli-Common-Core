/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:22:25 by eates             #+#    #+#             */
/*   Updated: 2023/07/29 14:07:45 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"
#include <unistd.h>

static int	ft_have_nl(char *s)
{
	if (!s)
		return (0);
	while (*s != '\0')
		if (*s++ == '\n')
			return (1);
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = -1;
	if (!stash)
		return (0);
	while (stash[++i] != '\n')
		;
	line = malloc(sizeof(char) * (++i + 1));
	if (!line)
		return (0);
	j = -1;
	while (++j < i)
		line[j] = stash[j];
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_stash(char *stash)
{
	size_t	i;
	char	*res;

	i = -1;
	if (!stash)
		return (NULL);
	while (stash[++i] != '\n')
		;
	if (stash[i + 1] == '\0')
		return (ft_free_stash(&stash, 0));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	return (ft_free_stash(&stash, 0), res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	while (ret > 0 && fd >= 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret == 0 && !stash) || ret == -1)
			return (ft_free_stash(&stash, 0));
		buf[ret] = '\0';
		stash = ft_copy_to_stash(stash, buf);
		if (ft_have_nl(stash))
		{
			line = ft_extract_line(stash);
			if (!line)
				return (ft_free_stash(&stash, 0));
			return (stash = ft_recreate_stash(stash), line);
		}
	}
	return (ft_free_stash(&stash, 1));
}

char	*get_next_line_bonus(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*stash[5000];
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	while (ret > 0 && fd >= 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret == 0 && !stash[fd]) || ret == -1)
			return (ft_free_stash(&stash[fd], 0));
		buf[ret] = '\0';
		stash[fd] = ft_copy_to_stash(stash[fd], buf);
		if (ft_have_nl(stash[fd]))
		{
			line = ft_extract_line(stash[fd]);
			if (!line)
				return (ft_free_stash(&stash[fd], 0));
			return (stash[fd] = ft_recreate_stash(stash[fd]), line);
		}
	}
	return (ft_free_stash(&stash[fd], 1));
}
