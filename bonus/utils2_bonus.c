/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:07:45 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 12:04:19 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"

int	has_and_pipe_or_that_is_first_element(t_ms *ms)
{
	if (ms->cmd->token == PIPE || ms->cmd->token == AND || ms->cmd->token == OR)
	{
		if (ms->cmd->token == PIPE)
			ms->tmp1 = "`|'";
		else if (ms->cmd->token == AND)
			ms->tmp1 = "`&&'";
		else if (ms->cmd->token == OR)
			ms->tmp1 = "`||'";
		write_error("minishell: syntax error ", "near unexpected token ",
			ms->tmp1);
		return (ms->tmp1 = NULL, 1);
	}
	return (0);
}

int	control_specifice_marks(t_ms *ms, t_cmd *tmp)
{
	if (has_and_pipe_or_that_is_first_element(ms))
		return (ms->status = 258);
	while (tmp)
	{
		if (tmp->token != NONE && tmp->token != CP)
		{
			if (!tmp->next)
				return (token_error(tmp, 0), ms->status = 258);
			else if ((tmp->token != OP
					|| ((tmp->next->token < 2 || tmp->next->token > 5)
						&& tmp->next->token != OP))
				&& (((tmp->token < 9 || tmp->token > 11)
						&& tmp->next->token != NONE)
					|| (tmp->token > 8 && tmp->token < 12
						&& tmp->next->token > 8 && tmp->next->token < 12)))
				return (token_error(tmp, 1), ms->status = 258);
		}
		else if (tmp->token == CP && tmp->next && tmp->next->token == OP)
			return (write_error("minishell: syntax error", " near unexpected",
					" token `)'"), ms->status = 258);
		tmp = tmp->next;
	}
	return (control_parantheses(ms));
}

int	control_specifice_marks_and_exec_heredoc(t_ms *ms)
{
	int		i;
	t_cmd	*tmp;

	count_pipe(ms);
	i = -1;
	ms->heredocs = malloc(sizeof(int *) * (ms->num_of_pipe + 2));
	if_error_frees(ms, ms->heredocs, 1);
	ms->heredocs[ms->num_of_pipe + 1] = NULL;
	while (++i <= ms->num_of_pipe)
	{
		ms->heredocs[i] = ft_calloc(2, sizeof(int));
		if_error_frees(ms, ms->heredocs[i], 1);
	}
	tmp = ms->cmd;
	return (ft_exec_heredoc(tmp, --i, ms));
}

void	count_pipe(t_ms *ms)
{
	t_cmd	*tmp;

	tmp = ms->cmd;
	while (tmp && tmp->token != AND && tmp->token != OR)
	{
		ms->num_of_pipe += (tmp->token == PIPE);
		tmp = tmp->next;
	}
}
