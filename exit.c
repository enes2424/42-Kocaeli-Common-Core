/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:33:00 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/21 13:55:05 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"

void	value_control(char *value, t_ms *ms, int i)
{
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
		{
			while (value[i] == ' ' || (value[i] >= 9 && value[i] <= 13))
				i++;
			if (!value[i])
				break ;
			write(2, "minishell: exit: ", 18);
			write(2, value, ft_strlen(value));
			write(2, ": numeric argument required\n", 29);
			frees(ms, 255);
		}
		i++;
	}
}

void	ft_exit(t_ms *ms)
{
	char	*value;
	int		i;

	if (!ms->cmd->next || ms->cmd->next->token == PIPE)
		frees(ms, ms->status);
	value = ms->cmd->next->value;
	i = 0;
	while (value[i] == ' ' || (value[i] >= 9 && value[i] <= 13))
		i++;
	i += (value[i] == '+' || value[i] == '-');
	value_control(value, ms, i);
	if (ms->cmd->next->next && ms->cmd->next->next->token != PIPE)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		ms->status = 1;
		return ;
	}
	frees(ms, ft_atoi(value));
}
