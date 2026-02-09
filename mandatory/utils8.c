/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:35:59 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 21:05:58 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"

void	linkedlistclear(t_linkedlist *lst)
{
	if (lst)
		linkedlistclear(lst->next);
	free(lst);
}

void	special_free(void	**var)
{
	free(*var);
	*var = NULL;
}

void	check_malloc(t_program *x, void *value)
{
	if (!value)
		free_program(ALLOC_ERR, x, 1);
}

int	control_rgb(t_program *x, char *str)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(str, " ");
	check_malloc(x, tmp);
	if (!ft_strlen(tmp))
		return (free(tmp), 1);
	i = (tmp[0] == '+') - 1;
	while (tmp[++i])
		if (!ft_isdigit(tmp[i]))
			return (free(tmp), 1);
	return (free(tmp), 0);
}
