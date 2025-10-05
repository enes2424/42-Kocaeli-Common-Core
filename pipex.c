/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:55:46 by eates             #+#    #+#             */
/*   Updated: 2023/10/20 17:11:00 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static void	init(t_pipex *pipex)
{
	pipex->cmd = NULL;
	pipex->cmd_paths = NULL;
	pipex->path = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipefd[3];

	init(&pipex);
	has_error_of_arg(argc, argv);
	if (pipe(pipefd + 1) == -1)
		return (perror("could not create pipe!"), 0);
	pipefd[0] = 0;
	while (envp[pipefd[0]] && ft_strncmp("PATH", envp[pipefd[0]], 4))
		pipefd[0]++;
	if (!envp[pipefd[0]])
		return (close(pipefd[1]), close(pipefd[2]),
			write(2, "Path not found!\n", 16), 1);
	pipex.cmd_paths = ft_split(envp[pipefd[0]] + 5, ':');
	if (!pipex.cmd_paths)
		return (close(pipefd[1]), close(pipefd[2]),
			write(2, "couldn't take space with malloc\n", 32), 0);
	return (pipex.pid1 = fork(),
		has_error_of_pid(pipex.pid1, pipex.cmd_paths),
		child1(pipex, pipefd + 1, argv, envp),
		waitpid(pipex.pid1, 0, 0), pipex.pid2 = fork(),
		has_error_of_pid(pipex.pid2, pipex.cmd_paths),
		child2(pipex, pipefd + 1, argv, envp),
		close(pipefd[2]), waitpid(pipex.pid2, 0, 0),
		close(pipefd[1]), free_string_array(pipex.cmd_paths), 0);
}
