/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:52:01 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 16:23:22 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

static void	token_error(t_cmd *tmp, int flag)
{
	if (flag == 0)
	{
		write(2, "minishell: syntax error near", 29);
		write(2, " unexpected token `newline'\n", 29);
	}
	if (flag == 1)
		write_error("minishell: syntax error near unexpected token `",
			tmp->next->value, "\'");
}

static int	control_specifice_marks(t_ms *ms)
{
	t_cmd	*tmp;

	if (ms->cmd->token == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (ms->status = 258);
	}
	tmp = ms->cmd;
	while (tmp)
	{
		if (tmp->token != NONE)
		{
			if (!tmp->next)
				return (token_error(tmp, 0), ms->status = 258);
			else if ((tmp->token != PIPE && tmp->next->token != NONE)
				|| (tmp->token == PIPE && tmp->next->token == PIPE))
				return (token_error(tmp, 1), ms->status = 258);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	control_specifice_marks_and_exec_heredoc(t_ms *ms)
{
	int		i;
	t_cmd	*tmp;
	int		status;

	i = -1;
	status = control_specifice_marks(ms);
	ms->heredocs = malloc(sizeof(int *) * (ms->num_of_pipe + 2));
	if_error_frees(ms, ms->heredocs, 1);
	ms->heredocs[ms->num_of_pipe + 1] = NULL;
	while (++i <= ms->num_of_pipe)
	{
		ms->heredocs[i] = ft_calloc(2, sizeof(int));
		if_error_frees(ms, ms->heredocs[i], 1);
	}
	tmp = ms->cmd;
	if (ft_exec_heredoc(tmp, --i, ms))
		return (1);
	if (status)
		ms->status = status;
	return (status);
}

static void	process_cmd(t_ms *ms)
{
	int	status;

	status = control_specifice_marks_and_exec_heredoc(ms);
	g_sig_control = 1;
	if (status || redirection(ms) || !ms->cmd)
		;
	else if (ft_strlen(ms->cmd->value) == 2 && !ms->num_of_pipe
		&& ft_tolower(ms->cmd->value[0]) == 'c'
		&& ft_tolower(ms->cmd->value[1]) == 'd')
		cd(ms);
	else if (!ft_strcmp(ms->cmd->value, "export")
		&& (ms->cmd->next && ms->cmd->next->token == NONE) && !ms->num_of_pipe)
		add_export(ms);
	else if (!ft_strcmp(ms->cmd->value, "unset")
		&& !ms->num_of_pipe)
		unset(ms);
	else if (!ft_strcmp(ms->cmd->value, "exit")
		&& !ms->num_of_pipe)
		ft_exit(ms);
	else
		execute(ms);
	return (dup2(STD_IN, 0), dup2(STD_OUT, 1),
		ft_free((void **)&(ms->input), 0),
		ms->main_cmd = free_cmd(ms->main_cmd), free_heredocs(ms),
		(void)(ms->num_of_pipe = 0));
}

int	main(int ac, char **av, char **ev)
{
	t_ms	ms;

	if (ac > 1)
		return (write(2, "This program can't take any argumans!!!\n", 41), 0);
	init(&ms, ev);
	sigcontrol();
	while (av[0])
	{
		create_pwd_and_name_and_home(&ms);
		g_sig_control = 0;
		ms.input = readline(ms.name);
		write(1, "\033[35m", 6);
		g_sig_control = ft_free((void **)&(ms.name), 1);
		if_error_frees(&ms, ms.input, 0);
		if (ft_strlen(ms.input))
			add_history(ms.input);
		else if (ft_free((void **)&ms.input, 1))
			continue ;
		if (create_cmd(&ms, ms.input))
			continue ;
		ms.is_prev_token_heredoc = 0;
		ms.main_cmd = ms.cmd;
		process_cmd(&ms);
	}
	return (0);
}
