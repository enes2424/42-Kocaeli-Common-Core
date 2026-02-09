/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:52:01 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 16:11:02 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>

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
	else if (!ft_strcmp(ms->cmd->value, "unset") && !ms->num_of_pipe)
		unset(ms);
	else if (!ft_strcmp(ms->cmd->value, "exit") && !ms->num_of_pipe)
		ft_exit(ms);
	else
		execute(ms);
	dup2(STD_IN, 0);
	dup2(STD_OUT, 1);
	ft_free((void **)&(ms->input), 0);
	return (ms->num_of_pipe = 0, free_heredocs(ms));
}

static void	ignore(t_ms *ms, int *depth)
{
	int		tmp_depth;

	tmp_depth = *depth;
	while (ms->cmd)
	{
		*depth += (ms->cmd->token == OP) - (ms->cmd->token == CP);
		if ((ms->cmd->token == AND || ms->cmd->token == OR)
			&& *depth <= tmp_depth)
			break ;
		ms->cmd = ms->cmd->next;
	}
}

static void	all_process_cmd(t_ms *ms, int depth)
{
	int		control;

	while (true)
	{
		control = (ms->cmd->token == AND) + 2 * (ms->cmd->token == OR);
		if (control)
			ms->cmd = ms->cmd->next;
		if (!control || (control == 1 && !ms->status)
			|| (control == 2 && ms->status))
		{
			while (ms->cmd && ms->cmd->token == OP && ++depth)
				ms->cmd = ms->cmd->next;
			process_cmd(ms);
		}
		else
			ignore(ms, &depth);
		while (ms->cmd && ms->cmd->token != AND && ms->cmd->token != OR)
		{
			depth -= ms->cmd->token == CP;
			ms->cmd = ms->cmd->next;
		}
		if (!ms->cmd)
			break ;
	}
}

static int	main2(t_ms *ms)
{
	create_pwd_and_name_and_home(ms);
	g_sig_control = 0;
	ms->input = readline(ms->name);
	write(1, "\033[35m", 6);
	g_sig_control = ft_free((void **)&(ms->name), 1);
	if_error_frees(ms, ms->input, 0);
	if (ft_strlen(ms->input))
		add_history(ms->input);
	else if (ft_free((void **)&ms->input, 1))
		return (1);
	if (create_cmd(ms, ms->input))
		return (1);
	ms->is_prev_token_heredoc = 0;
	wilcards_operations(ms, take_files_and_directories(ms));
	return (ms->main_cmd = ms->cmd, 0);
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
		if (main2(&ms))
			continue ;
		if (control_specifice_marks(&ms, ms.cmd))
			control_specifice_marks_and_exec_heredoc(&ms);
		else
		{
			clear_extra_parantheses(&ms);
			ms.cmd = ms.main_cmd;
			all_process_cmd(&ms, 0);
			ms.main_cmd = free_cmd(ms.main_cmd);
		}
	}
	return (0);
}
