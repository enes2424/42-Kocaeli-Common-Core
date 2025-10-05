/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:57:58 by eates             #+#    #+#             */
/*   Updated: 2023/10/12 14:12:18 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	has_error_of_arg(int argc, char **argv)
{
	if (argc != 5)
	{
		write(2, "missing argument or excess argument!\n", 37);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK))
	{
		write(2, "no such file or directory: ", 27);
		write(2, argv[1], ft_strlen(argv[1]));
		write(1, "\n", 1);
		exit(0);
	}
}

void	has_error_of_pid(pid_t pid, char **str)
{
	if (pid < 0)
	{
		free_string_array(str);
		perror("fork did not work!");
		exit(EXIT_FAILURE);
	}
}

static void	create_path(t_pipex *pipex)
{
	char	*tmp;
	int		i;

	i = -1;
	while (pipex->cmd_paths[++i])
	{
		if (pipex->path)
			free(pipex->path);
		tmp = ft_strjoin(pipex->cmd_paths[i], "/");
		if (!tmp)
			return (perror("couldn't take space with malloc"),
				finish(pipex), exit(EXIT_FAILURE));
		pipex->path = ft_strjoin(tmp, pipex->cmd[0]);
		if (!pipex->path)
			return (perror("couldn't take space with malloc"),
				finish(pipex), exit(EXIT_FAILURE));
		free(tmp);
		if (!access((*pipex).path, F_OK))
			return ;
	}
	return (write(2, "command not found: ", 19),
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0])),
		write(2, "\n", 1),
		finish(pipex), exit(EXIT_FAILURE));
}

void	child1(t_pipex pipex, int *pipefd, char **argv, char **envp)
{
	if (pipex.pid1 != 0)
		return ;
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	pipex.filefd1 = open(argv[1], O_RDONLY);
	if (pipex.filefd1 == -1)
		return (perror("file1 was not opened"),
			finish(&pipex), exit(EXIT_FAILURE));
	dup2(pipex.filefd1, 0);
	close(pipex.filefd1);
	pipex.cmd = ft_split(argv[2], ' ');
	if (!pipex.cmd)
		return (perror("couldn't take space with malloc"),
			finish(&pipex), exit(EXIT_FAILURE));
	pipex.filefd2 = open(argv[4], O_CREAT, 0000644);
	if (pipex.filefd2 == -1)
		return (perror("file2 was not opened"),
			finish(&pipex), exit(EXIT_FAILURE));
	close(pipex.filefd2);
	create_path(&pipex);
	free_string_array(pipex.cmd_paths);
	execve(pipex.path, pipex.cmd, envp);
	return (free(pipex.path),
		free_string_array(pipex.cmd), perror("execve"), exit(EXIT_FAILURE));
}

void	child2(t_pipex pipex, int *pipefd, char **argv, char **envp)
{
	if (pipex.pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		pipex.filefd2 = open(argv[4], O_TRUNC | O_WRONLY, 0000644);
		if (pipex.filefd2 == -1)
			return (perror("file2 was not opened"),
				finish(&pipex), exit(EXIT_FAILURE));
		dup2(pipex.filefd2, 1);
		close(pipex.filefd2);
		pipex.cmd = ft_split(argv[3], ' ');
		if (!pipex.cmd)
			return (perror("couldn't take space with malloc"),
				finish(&pipex), exit(EXIT_FAILURE));
		create_path(&pipex);
		free_string_array(pipex.cmd_paths);
		execve(pipex.path, pipex.cmd, envp);
		return (free(pipex.path),
			free_string_array(pipex.cmd), perror("execve"), exit(EXIT_FAILURE));
	}
}
