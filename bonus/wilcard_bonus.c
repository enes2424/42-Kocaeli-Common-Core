/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:43:51 by eates             #+#    #+#             */
/*   Updated: 2024/01/23 13:30:51 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

int	is_wilcards(char *str1, char *str2)
{
	while (*str1 && *str2 && *str2 != '*' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2 && !*str1)
		return (1);
	if (*str2 == '*')
	{
		while (*str2 == '*')
			str2++;
		while (*str1)
		{
			if (is_wilcards(str1, str2))
				return (1);
			str1++;
		}
		if (is_wilcards(str1, str2))
			return (1);
	}
	return (0);
}

int	load_files(t_ms *ms, int *pipefd, pid_t pid)
{
	char	**env;
	char	**cmd;
	int		exit_status;

	if (pid < 0 && ft_putendl_fd("Fork error!!", 2))
		frees(ms, 1);
	else if (!pid)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		frees3(ms);
		free_cmd(ms->main_cmd);
		env = convert_t_env_to_str_array(ms, NULL, 0);
		cmd = malloc(sizeof(char *) * 2);
		if_error_frees(ms, cmd, 1);
		return (cmd[0] = "ls", cmd[1] = NULL, execve("/bin/ls", cmd, env),
			write(2, "Execve error!!\n", 16), free(cmd),
			ft_free_malloc(env), exit(1), 1);
	}
	waitpid(pid, &exit_status, 0);
	close(pipefd[1]);
	if (exit_status)
		return (ms->status = exit_status);
	return (0);
}

char	**take_files_and_directories(t_ms *ms)
{
	int		pipefd[2];
	char	**arr;
	char	buf[2];
	int		len;

	buf[1] = 0;
	if (pipe(pipefd) == -1 && write(2, "Pipe error!!\n", 14))
		frees(ms, 1);
	if (load_files(ms, pipefd, fork()))
		return (NULL);
	ms->tmp1 = ft_strdup("");
	if (!ms->tmp1 && !close(pipefd[0]))
		frees(ms, 1);
	len = read(pipefd[0], buf, 1);
	while (len > 0)
	{
		ms->tmp2 = ms->tmp1;
		ms->tmp1 = ft_strjoin(ms->tmp1, buf);
		ft_free((void **)&ms->tmp2, 0);
		if (!ms->tmp1 && !close(pipefd[0]))
			frees(ms, 1);
		len = read(pipefd[0], buf, 1);
	}
	return (close(pipefd[0]), arr = ft_split(ms->tmp1, '\n'),
		ft_free((void **)&ms->tmp1, 0), arr);
}

void	wilcards_operations2(t_ms *ms, t_cmd **tmp,
	char **files_and_directories, int *i)
{
	if (!is_wilcards(files_and_directories[i[0]], ms->tmp2))
		return ;
	if (!i[1])
	{
		ms->tmp1 = tmp[0]->value;
		tmp[0]->value = ft_strdup(files_and_directories[i[0]]);
		ft_free((void **)&ms->tmp1, 0);
		if (!tmp[0]->value && !ft_free_malloc(files_and_directories))
			frees(ms, 1);
	}
	else
	{
		tmp[1] = ft_calloc(1, sizeof(t_cmd));
		if (!tmp[1]
			&& !ft_free_malloc(files_and_directories))
			frees(ms, 1);
		tmp[1]->value = ft_strdup(files_and_directories[i[0]]);
		tmp[1]->token = NONE;
		if (!tmp[1]->value && !ft_free_malloc(files_and_directories)
			&& ft_free((void **)&tmp[1], 1))
			frees(ms, 1);
		tmp[1]->next = tmp[0]->next;
		tmp[0]->next = tmp[1];
	}
	i[1]++;
}

void	wilcards_operations(t_ms *ms, char **files_and_directories)
{
	t_cmd	*tmp[2];
	int		i[2];

	if_error_frees(ms, files_and_directories, 1);
	tmp[0] = ms->cmd;
	while (tmp[0])
	{
		if (tmp[0]->token == WILCARD)
		{
			i[0] = -1;
			i[1] = 0;
			ms->tmp2 = ft_strdup(tmp[0]->value);
			if (!ms->tmp2 && !ft_free_malloc(files_and_directories))
				frees(ms, 1);
			while (files_and_directories[++i[0]])
				wilcards_operations2(ms, tmp, files_and_directories, i);
			ft_free((void **)&ms->tmp2, 0);
			tmp[0]->token = NONE;
		}
		else if (tmp[0]->token == HEREDOC
			&& tmp[0]->next && tmp[0]->next->token == WILCARD)
			tmp[0]->next->token = NONE;
		tmp[0] = tmp[0]->next;
	}
	ft_free_malloc(files_and_directories);
}
