/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:17:14 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/22 20:06:02 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"

void	token_error(t_cmd *tmp, int flag)
{
	if (flag == 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
	if (flag == 1)
		write_error("minishell: syntax error near unexpected token `",
			tmp->next->value, "'");
}

int	control_parantheses(t_ms *ms)
{
	t_cmd	*tmp;
	int		control;

	tmp = ms->cmd;
	control = 0;
	while (tmp)
	{
		control += (tmp->token == OP) - (tmp->token == CP);
		if (control < 0)
			return (write_error("minishell: syntax error", " near unexpected",
					" token `)'"), ms->status = 258);
		tmp = tmp->next;
	}
	if (control > 0)
		return (write_error("minishell: syntax error", " near unexpected",
				" token `('"), ms->status = 258);
	return (0);
}
