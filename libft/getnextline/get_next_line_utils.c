/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:07:07 by eates             #+#    #+#             */
/*   Updated: 2023/07/29 14:07:11 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*res;

	if (!stash && buf)
		return (ft_strdup(buf));
	return (res = ft_strjoin(stash, buf), ft_free_stash(&stash, 0), res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	j;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (ret && start <= (unsigned int)ft_strlen(s) && j <= len)
		ret[j++] = s[start++];
	return (ret);
}

void	*ft_free_stash(char **stash, int create_line)
{
	char	*line;

	if (create_line == 0 && *stash)
		free(*stash);
	else if (create_line == 1 && *stash)
		return (line = ft_strdup(*stash), free(*stash), *stash = 0, line);
	return (*stash = 0);
}
