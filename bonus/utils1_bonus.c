/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:13 by eates             #+#    #+#             */
/*   Updated: 2024/01/21 17:06:54 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

int	add_char_to_str(char **str, char c)
{
	char	*tmp;
	int		i;

	tmp = *str;
	*str = malloc(ft_strlen(tmp) + 2);
	if (!*str)
		return (ft_free((void **)&tmp, 0), 1);
	i = -1;
	while (tmp[++i])
		(*str)[i] = tmp[i];
	return (ft_free((void **)&tmp, 0), (*str)[i] = c, (*str)[++i] = 0, 0);
}

char	**sort(char **ev)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (ev[++i])
	{
		j = -1;
		while (ev[++j])
		{
			if (ft_strcmp(ev[i], ev[j]) < 0)
			{
				tmp = ev[i];
				ev[i] = ev[j];
				ev[j] = tmp;
			}
		}
	}
	return (ev);
}

void	write_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
}

int	control(char *key, int status)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (write_error("minishell: export: `",
				key, "': not a valid identifier"), 1);
	i = 0;
	while (key[++i])
	{
		if (key[i] == '=')
		{
			if (status)
				write_error("minishell: export: `",
					key, "': not a valid identifier");
			return (status);
		}
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (write_error("minishell: export: `",
					key, "': not a valid identifier"), 1);
	}
	return (0);
}
