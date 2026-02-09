/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:51 by eates             #+#    #+#             */
/*   Updated: 2024/01/22 19:26:56 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

char	*convert(t_ms *ms, char *str)
{
	int		i;
	char	*new_str;

	new_str = ft_strdup(str);
	if_error_frees(ms, new_str, 1);
	i = -1;
	while (new_str[++i])
		new_str[i] = ft_tolower(new_str[i]);
	return (new_str);
}

void	ft_builtins(t_ms *ms)
{
	if (ft_strlen(ms->cmd->value) == 2
		&& ft_tolower(ms->cmd->value[0]) == 'c'
		&& ft_tolower(ms->cmd->value[1]) == 'd')
	{
		cd(ms);
		frees(ms, 0);
	}
	if (!ft_strcmp(ms->convert_str, "env"))
		env(ms);
	if (!ft_strcmp(ms->convert_str, "echo"))
		echo(ms);
	if (!ft_strcmp(ms->cmd->value, "export"))
		export(ms);
	if (!ft_strcmp(ms->cmd->value, "unset"))
	{
		unset(ms);
		frees(ms, ms->status);
	}
	if (!ft_strcmp(ms->cmd->value, "exit"))
	{
		ft_exit(ms);
		frees(ms, ms->status);
	}
}

void	ft_exec(t_ms *ms)
{
	char	**cmd;
	char	**env;

	redirection(ms);
	if (!ms->cmd || ms->cmd->token != NONE)
		frees(ms, 0);
	ms->convert_str = convert(ms, ms->cmd->value);
	ft_builtins(ms);
	if (!ft_strcmp(ms->convert_str, "pwd"))
		return (ft_putendl_fd(ms->pwd, 1), frees(ms, 0));
	ms->path = create_path(ms, NULL, -1);
	cmd = llist_cmd_to_cmd(ms);
	env = convert_t_env_to_str_array(ms, cmd, 0);
	frees3(ms);
	execve(ms->path, cmd, env);
	write(2, "Execve error!!\n", 16);
	ft_free_malloc(env);
	ft_free_malloc(cmd);
	ms->main_cmd = NULL;
	ms->env = NULL;
	frees(ms, 1);
}

void	pipe2(t_ms *ms, int *pid, int *pipefd)
{
	if (ms->num_of_pipe)
	{
		pid[1] = fork();
		if (pid[1] < 0)
			return (write(2, "Fork error!!\n", 14), frees(ms, 1));
		else if (!pid[1])
		{
			close(pipefd[1]);
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			ms->num_of_pipe--;
			while (ms->cmd && ms->cmd->token == NONE)
				ms->cmd = ms->cmd->next;
			if (ms->cmd)
				ms->cmd = ms->cmd->next;
			return (execute(ms), frees(ms, ms->status));
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
	waitpid(pid[0], &ms->status, 0);
	if (ms->num_of_pipe)
		waitpid(pid[1], &ms->status, 0);
}

void	execute(t_ms *ms)
{
	pid_t	pid[2];
	int		pipefd[2];

	if (ms->num_of_pipe && pipe(pipefd) == -1)
		return (write(2, "Pipe error!!\n", 14), frees(ms, 1));
	pid[0] = fork();
	if (pid[0] < 0)
		return (write(2, "Fork error!!\n", 14), frees(ms, 1));
	else if (!pid[0])
	{
		if (ms->num_of_pipe)
		{
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
		}
		ft_exec(ms);
	}
	pipe2(ms, pid, pipefd);
	ms->status /= 256;
	if (!ms->status && g_sig_control == 2 && !ms->num_of_pipe)
		ms->status = 130;
	else if (!ms->status && g_sig_control == 3 && !ms->num_of_pipe)
		ms->status = 131;
}
