/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:51:46 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 12:13:31 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	edit_cmd(t_ms *ms, int *status, char *input, t_cmd *tmp)
{
	ms->tmp1 = ft_strdup("");
	if_error_frees(ms, ms->tmp1, 1);
	while (*input == ' ')
		input++;
	while (*input)
	{
		if (!status[0] && *input != ';' && *input != '\\')
			input = operations_w_q(ms, input, status, &tmp);
		else if (status[0])
		{
			status[1] = 2;
			if ((status[0] == 1 && *input == '\"')
				|| (status[0] == 2 && *input == '\''))
				status[0] = 0;
			else if (status[0] == 1 && *input == '$'
				&& (ft_isalnum(*(input + 1)) || *(input + 1) == '_'
					|| *(input + 1) == '?') && !ms->is_prev_token_heredoc)
				input = dolar_mark(ms, input, 2 * (*(input + 1) == '?')) - 1;
			else if (add_char_to_str(&ms->tmp1, *input))
				frees(ms, 1);
		}
		input++;
	}
	return (end_edit_cmd(ms, status, tmp),
		(void)ft_free((void **)&ms->tmp1, 0));
}

int	create_cmd(t_ms *ms, char *input)
{
	int		count[2];
	int		status[2];

	count[0] = 0;
	count[1] = 0;
	while (*input)
	{
		count[0] += (*input == '\"') * (count[1] % 2 == 0);
		count[1] += (*input == '\'') * (count[0] % 2 == 0);
		input++;
	}
	if (count[0] % 2 || count[1] % 2)
		return (ft_free((void **)&ms->input, 0), ms->status = 1,
			ft_putendl_fd("There is unclosed quotes", 2));
	status[0] = (*ms->input == '\"') + 2 * (*ms->input == '\'');
	input = ms->input;
	while (*input == ' ')
		input++;
	if (!*input)
		return (ft_free((void **)&ms->input, 0), 1);
	input = ms->input + (status[0] != 0);
	ms->cmd = ft_calloc(1, sizeof(t_cmd));
	if_error_frees(ms, ms->cmd, 1);
	return (status[1] = 1, edit_cmd(ms, status, input, ms->cmd), 0);
}
