/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:02:24 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 12:30:06 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"

char	*add_cmd(t_ms *ms, t_cmd **tmp, char *input)
{
	ms->is_prev_token_heredoc = 0;
	(*tmp)->value = ft_strdup(ms->tmp1);
	if (ms->is_wilcard)
		(*tmp)->token = WILCARD;
	else
		(*tmp)->token = NONE;
	ms->is_wilcard = 0;
	while (*input == ' ')
		input++;
	ft_free((void **)&ms->tmp1, 0);
	ms->tmp1 = ft_strdup("");
	if (!ms->tmp1)
		frees(ms, 1);
	(*tmp)->next = ft_calloc(1, sizeof(t_cmd));
	if (!(*tmp)->next)
		frees(ms, 1);
	return ((*tmp) = (*tmp)->next, --input);
}

char	*operations_w_q(t_ms *ms, char *input, int *status, t_cmd **tmp)
{
	input = while_loop(ms, input, status[1], tmp);
	status[1] = 1;
	if (*input == '*')
		ms->is_wilcard = 1;
	if (*input == ' ')
		input = add_cmd(ms, tmp, input);
	else if (*input == '$' && (ft_isalnum(*(input + 1))
			|| *(input + 1) == '_' || *(input + 1) == '?')
		&& !ms->is_prev_token_heredoc)
		input = dolar_mark(ms, input, 2 * (*(input + 1) == '?')) - 1;
	else if (*input == '\'' || *input == '\"')
		status[0] = (*input == '\"') + 2 * (*input == '\'');
	else if (!*input)
		return (ft_free((void **)&ms->tmp1, 0), status[1] = 0, input - 1);
	else if (add_char_to_str(&ms->tmp1, *input))
		frees(ms, 1);
	return (input);
}

void	end_edit_cmd(t_ms *ms, int *status, t_cmd *tmp)
{
	if (status[1] && ms->input[ft_strlen(ms->input) - 1] != ' ')
		edit_end_element(ms, tmp, ms->tmp1, status[1]);
	tmp = ms->cmd;
	if (tmp->next)
	{
		while (tmp->next->next)
			tmp = tmp->next;
		if (!tmp->next->value)
			ft_free((void **)&tmp->next, 0);
	}
	else if (!tmp->value)
		ft_free((void **)&ms->cmd, 0);
}

char	**llist_cmd_to_cmd(t_ms *ms)
{
	char	**cmds;
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = ms->cmd;
	while (++i && tmp && tmp->token == NONE)
		tmp = tmp->next;
	cmds = ft_calloc(i, sizeof(char *));
	if_error_frees(ms, cmds, 1);
	i = -1;
	tmp = ms->cmd;
	while (tmp && tmp->token == NONE)
	{
		cmds[++i] = ft_strdup(tmp->value);
		if (!cmds[i])
		{
			ft_free_malloc(cmds);
			frees(ms, 1);
		}
		tmp = tmp->next;
	}
	return (free_cmd(ms->main_cmd), cmds);
}
