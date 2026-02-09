/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:07:21 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/22 17:33:42 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	heredocc(char *str, int *pipefd)
{
	char	*input;

	input = readline("> ");
	while (input && ft_strcmp(input, str))
	{
		ft_putendl_fd(input, pipefd[1]);
		free(input);
		input = readline("> ");
	}
	free(str);
	free(input);
	close(pipefd[1]);
	exit(0);
}

static int	heredoc(t_ms *ms, char *str)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1 && write(2, "Pipe error!!\n", 14))
		frees(ms, 1);
	g_sig_control = 5;
	pid = fork();
	if (pid < 0 && write(2, "Fork error!!\n", 14))
		frees(ms, 1);
	if (!pid)
	{
		str = ft_strdup(str);
		if_error_frees(ms, str, 1);
		frees4(ms);
		g_sig_control = 4;
		close(pipefd[0]);
		heredocc(str, pipefd);
	}
	return (waitpid(pid, &ms->status, 0), ms->status /= 256,
		close(pipefd[1]), pipefd[0]);
}

int	ft_exec_heredoc(t_cmd *tmp, int i, t_ms *ms)
{
	while (tmp)
	{
		if (tmp->token == PIPE)
			i--;
		else if (tmp->token == HEREDOC && tmp->next && tmp->next->token == NONE)
		{
			if (ms->heredocs[i][1])
				close(ms->heredocs[i][0]);
			ms->heredocs[i][0] = heredoc(ms, tmp->next->value);
			if (ms->status == 1)
				return (1);
			ms->heredocs[i][1] = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}
