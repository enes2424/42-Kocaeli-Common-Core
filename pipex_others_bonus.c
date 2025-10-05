/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_others_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:57:58 by eates             #+#    #+#             */
/*   Updated: 2023/10/12 14:39:02 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "getnextline/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	has_error_of_arg(t_pipex *pipex)
{
	if (pipex->argc < 5)
	{
		finish(pipex, 1);
		write(2, "missing argument!\n", 18);
		exit(EXIT_FAILURE);
	}
	pipex->control = !ft_strncmp(pipex->argv[1], "here_doc", 9);
	if (!pipex->control && access(pipex->argv[1], F_OK))
	{
		finish(pipex, 1);
		write(2, "no such file or directory: ", 27);
		write(2, pipex->argv[1], ft_strlen(pipex->argv[1]));
		write(1, "\n", 1);
		exit(0);
	}
}

void	has_error_of_pid(t_pipex *pipex, pid_t pid)
{
	if (pid < 0)
		return (finish(pipex, 1),
			perror("fork did not work!"), exit(EXIT_FAILURE));
}

void	create_path(t_pipex *pipex)
{
	char	*tmp;
	char	**tmp_cmd_paths;

	tmp_cmd_paths = pipex->cmd_paths;
	while (*tmp_cmd_paths)
	{
		if (pipex->cmd)
			free(pipex->cmd);
		tmp = ft_strjoin(*tmp_cmd_paths, "/");
		if (!tmp)
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(EXIT_FAILURE));
		pipex->cmd = ft_strjoin(tmp, pipex->str[0]);
		if (!pipex->cmd)
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(EXIT_FAILURE));
		free(tmp);
		if (!access((*pipex).cmd, F_OK))
			return ;
		tmp_cmd_paths++;
	}
	return (write(2, "command not found: ", 19),
		write(2, pipex->str[0], ft_strlen(pipex->str[0])),
		write(2, "\n", 1),
		finish(pipex, 1), exit(EXIT_FAILURE));
}

void	here_doc_operation(t_pipex *pipex, char *input)
{
	if (pipex->control)
	{
		if (pipe(pipex->pipefd_limiter) == -1)
			return (perror("could not create pipe!"), exit(1));
		write(1, "heredoc> ", 9);
		input = get_next_line(0);
		if (!input)
			write(1, "\n", 1);
		input[ft_strlen(input) - 1] = 0;
		while (input && ft_strncmp(input, pipex->argv[2],
				ft_strlen(pipex->argv[2]) + 1))
		{
			write(pipex->pipefd_limiter[1], input, ft_strlen(input));
			write(pipex->pipefd_limiter[1], "\n", 1);
			free(input);
			write(1, "heredoc> ", 9);
			input = get_next_line(0);
			input[ft_strlen(input) - 1] = 0;
		}
		if (input)
			free(input);
		else
			write(1, "\n", 1);
		close(pipex->pipefd_limiter[1]);
	}
}

void	dup_input(t_pipex *pipex)
{
	if (!pipex->control)
	{
		pipex->filefd1 = open(pipex->argv[1], O_RDONLY);
		if (pipex->filefd1 == -1)
			return (write(2, "file was not opened\n", 20),
				exit(EXIT_FAILURE));
		dup2(pipex->filefd1, 0);
		close(pipex->filefd1);
	}
	else
	{
		dup2(pipex->pipefd_limiter[0], 0);
		close(pipex->pipefd_limiter[0]);
	}
}
