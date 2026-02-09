/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expressions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:34:35 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 12:16:24 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	special_expression(t_ms *ms, t_cmd *tmp, char *str, int status)
{
	ms->is_prev_token_heredoc = (status == HEREDOC);
	tmp->value = ft_strdup(str);
	if_error_frees(ms, tmp->value, 1);
	return (tmp->token = status, 1);
}

char	*inopi(t_ms *ms, t_cmd **tmp, char *input)
{
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			input += special_expression(ms, *tmp, "<<", HEREDOC);
		else
			special_expression(ms, *tmp, "<", INPUT);
	}
	else if (*input == '>')
	{
		if (*(input + 1) == '>')
			input += special_expression(ms, *tmp, ">>", WRITE);
		else
			special_expression(ms, *tmp, ">", REWRITE);
	}
	else if (*input == '|')
	{
		ms->num_of_pipe++;
		special_expression(ms, *tmp, "|", PIPE);
	}
	input++;
	while (*input == ' ')
		input++;
	return (input);
}

char	*while_loop(t_ms *ms, char *input, int flag, t_cmd **tmp)
{
	while (*input == '<' || *input == '>' || *input == '|')
	{
		if (flag && input != ms->input && *(input - 1) != ' ')
		{
			(*tmp)->value = ms->tmp1;
			ms->tmp1 = ft_strdup("");
			if_error_frees(ms, ms->tmp1, 1);
			(*tmp)->token = NONE;
			(*tmp)->next = ft_calloc(1, sizeof(t_cmd));
			if_error_frees(ms, (*tmp)->next, 1);
			(*tmp) = (*tmp)->next;
		}
		input = inopi(ms, tmp, input);
		(*tmp)->next = ft_calloc(1, sizeof(t_cmd));
		if_error_frees(ms, (*tmp)->next, 1);
		(*tmp) = (*tmp)->next;
		flag = 0;
	}
	return (input);
}

char	*dolar_mark(t_ms *ms, char *input, int flag)
{
	if (flag)
	{
		ms->tmp2 = ft_itoa(ms->status);
		if_error_frees(ms, ms->tmp2, 1);
	}
	else
	{
		ms->tmp2 = ++input;
		while (ft_isalnum(*input) || *input == '_')
			input++;
		ms->tmp3 = ft_substr(ms->tmp2, 0, input - ms->tmp2);
		if_error_frees(ms, ms->tmp3, 1);
		ms->tmp2 = get_env(ms, ms->tmp3);
		ft_free((void **)&ms->tmp3, 0);
		if (!ms->tmp2)
			return (input);
	}
	ms->tmp3 = ms->tmp1;
	ms->tmp1 = ft_strjoin(ms->tmp1, ms->tmp2);
	if_error_frees(ms, ms->tmp1, 1);
	ft_free((void **)&ms->tmp3, 0);
	return (ft_free((void **)&ms->tmp2, 0), input + flag);
}

void	edit_end_element(t_cmd *tmp, char *str, int flag)
{
	tmp->value = ft_strdup(str);
	if (flag == 2)
		tmp->token = NONE;
	else if (!ft_strncmp(str, "<<", 3))
		tmp->token = HEREDOC;
	else if (!ft_strncmp(str, "<", 2))
		tmp->token = INPUT;
	else if (!ft_strncmp(str, ">>", 3))
		tmp->token = WRITE;
	else if (!ft_strncmp(str, ">", 2))
		tmp->token = REWRITE;
	else if (!ft_strncmp(str, "|", 2))
		tmp->token = PIPE;
	else
		tmp->token = NONE;
}
