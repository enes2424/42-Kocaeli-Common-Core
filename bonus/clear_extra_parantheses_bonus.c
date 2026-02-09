/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_extra_parantheses_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:50:32 by eates             #+#    #+#             */
/*   Updated: 2024/01/23 13:07:26 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <stdlib.h>

static int	clear_extra_parantheses3(t_cmd *tmp, int depth, int tmp_depth)
{
	t_cmd	*tmp2;
	t_cmd	*tmp3;

	tmp2 = tmp->next;
	while (1)
	{
		depth += (tmp2->next->token == OP) - (tmp2->next->token == CP);
		if (depth == tmp_depth)
			break ;
		tmp2 = tmp2->next;
	}
	if (tmp->token == PIPE
		|| (tmp2->next->next && tmp2->next->next->token == PIPE))
	{
		tmp3 = tmp->next;
		tmp->next = tmp->next->next;
		free(tmp3->value);
		free(tmp3);
		tmp3 = tmp2->next;
		tmp2->next = tmp2->next->next;
		free(tmp3->value);
		free(tmp3);
		return (1);
	}
	return (0);
}

static void	clear_extra_parantheses2(t_ms *ms)
{
	t_cmd	*tmp;
	int		tmp_depth;
	int		depth;

	depth = 0;
	tmp = ms->main_cmd;
	while (tmp->next)
	{
		tmp_depth = depth;
		if (tmp->next->token == OP
			&& clear_extra_parantheses3(tmp, depth + 1, tmp_depth))
			continue ;
		depth -= (tmp->next->token == CP);
		tmp = tmp->next;
	}
}

void	clear_extra_parantheses(t_ms *ms)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		depth;

	while (ms->main_cmd && ms->main_cmd->token == OP)
	{
		tmp = ms->main_cmd;
		depth = 1;
		while (depth + (tmp->next->token == OP) - (tmp->next->token == CP))
		{
			depth += (tmp->next->token == OP) - (tmp->next->token == CP);
			tmp = tmp->next;
		}
		if (!tmp->next->next || tmp->next->next->token != PIPE)
			break ;
		tmp2 = ms->main_cmd;
		ms->main_cmd = ms->main_cmd->next;
		free(tmp2->value);
		free(tmp2);
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		free(tmp2->value);
		free(tmp2);
	}
	clear_extra_parantheses2(ms);
}
