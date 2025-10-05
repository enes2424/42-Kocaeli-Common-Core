/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:56:24 by eates             #+#    #+#             */
/*   Updated: 2023/10/07 18:24:57 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	child1(t_pipex *pipex)
{
	here_doc_operation(pipex, NULL);
	pipex->pid[0] = fork();
	has_error_of_pid(pipex, pipex->pid[0]);
	if (pipex->pid[0] == 0)
	{
		close(pipex->pipefd[0][0]);
		dup2(pipex->pipefd[0][1], 1);
		close(pipex->pipefd[0][1]);
		dup_input(pipex);
		pipex->str = ft_split(pipex->argv[2 + pipex->control], ' ');
		if (!pipex->str)
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(EXIT_FAILURE));
		pipex->filefd2 = open(pipex->argv[pipex->argc - 1], O_CREAT, 0000644);
		if (pipex->filefd2 == -1)
			return (write(2, "file was not opened\n", 20), exit(EXIT_FAILURE));
		return (close(pipex->filefd2), create_path(pipex), finish(pipex, 0),
			execve(pipex->cmd, pipex->str, pipex->envp),
			free(pipex->cmd), free_double_array((void **)pipex->str),
			perror("execve"), exit(EXIT_FAILURE));
	}
	if (pipex->control)
		close(pipex->pipefd_limiter[0]);
	waitpid(pipex->pid[0], 0, 0);
}

void	child2(t_pipex *pipex)
{
	if (pipex->pid[pipex->argc - 4] == 0)
	{
		close(pipex->pipefd[pipex->argc - 5][1]);
		dup2(pipex->pipefd[pipex->argc - 5][0], 0);
		close(pipex->pipefd[pipex->argc - 5][0]);
		if (pipex->control)
			pipex->filefd2 = open(pipex->argv[pipex->argc - 1],
					O_APPEND | O_WRONLY, 0000644);
		else
			pipex->filefd2 = open(pipex->argv[pipex->argc - 1],
					O_TRUNC | O_WRONLY, 0000644);
		if (pipex->filefd2 == -1)
			return (write(2, "file was not opened\n", 20), exit(EXIT_FAILURE));
		dup2(pipex->filefd2, 1);
		close(pipex->filefd2);
		pipex->str = ft_split(pipex->argv[pipex->argc - 2], ' ');
		if (!pipex->str)
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(EXIT_FAILURE));
		return (create_path(pipex), finish(pipex, 0),
			execve(pipex->cmd, pipex->str, pipex->envp),
			free(pipex->cmd), free_double_array((void **)pipex->str),
			perror("execve"), exit(EXIT_FAILURE));
	}
	close(pipex->pipefd[pipex->argc - 5][1]);
}

void	child(t_pipex *pipex, int index)
{
	if (pipe(pipex->pipefd[index]) == -1)
		return (write(2, "Pipe olusturulamadi!\n", 21), exit(0));
	pipex->pid[index] = fork();
	has_error_of_pid(pipex, pipex->pid[index]);
	if (pipex->pid[index] == 0)
	{
		close(pipex->pipefd[index - 1][1]);
		dup2(pipex->pipefd[index - 1][0], 0);
		close(pipex->pipefd[index - 1][0]);
		close(pipex->pipefd[index][0]);
		dup2(pipex->pipefd[index][1], 1);
		close(pipex->pipefd[index][1]);
		pipex->str = ft_split(pipex->argv[index + 2 + pipex->control], ' ');
		if (!pipex->str)
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(EXIT_FAILURE));
		create_path(pipex);
		finish(pipex, 0);
		execve(pipex->cmd, pipex->str, pipex->envp);
		return (free(pipex->cmd), free_double_array((void **)pipex->str),
			perror("execve"), exit(EXIT_FAILURE));
	}
	close(pipex->pipefd[index - 1][1]);
	close(pipex->pipefd[index - 1][0]);
	waitpid(pipex->pid[index], 0, 0);
}
