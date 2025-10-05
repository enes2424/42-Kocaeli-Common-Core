/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:55:46 by eates             #+#    #+#             */
/*   Updated: 2023/10/20 17:17:50 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static inline void	pre_operation(t_pipex *pipex, int argc, char **argv, int i)
{
	pipex->argc = argc;
	pipex->argv = argv;
	has_error_of_arg(pipex);
	pipex->pipefd = malloc(sizeof(int *) * (argc - 3));
	if (!pipex->pipefd)
		return (perror("couldn't take space with malloc"), exit(1));
	while (++i < argc - 4)
	{
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipefd[i])
			return (perror("couldn't take space with malloc"),
				finish(pipex, 1), exit(1));
	}
	pipex->pipefd[i] = NULL;
	pipex->pid = malloc(sizeof(t_pipex) * (argc - 3));
	if (!pipex->pid)
		return (perror("couldn't take space with malloc"),
			finish(pipex, 1), exit(1));
	if (pipe(pipex->pipefd[0]) == -1)
		return (write(2, "Pipe olusturulamadi!\n", 21), exit(1));
}

static void	init(t_pipex *pipex)
{
	pipex->control = 0;
	pipex->pid = NULL;
	pipex->pipefd = NULL;
	pipex->cmd = NULL;
	pipex->cmd_paths = NULL;
	pipex->str = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	init(&pipex);
	pre_operation(&pipex, argc, argv, -1);
	pipex.envp = envp;
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return (close(pipex.pipefd[0][0]), close(pipex.pipefd[0][1]),
			write(2, "Path not found!\n", 16), 1);
	pipex.cmd_paths = ft_split(*envp + 5, ':');
	if (!pipex.cmd_paths)
		return (close(pipex.pipefd[0][0]), close(pipex.pipefd[0][1]),
			finish(&pipex, 1), perror("couldn't take space with malloc"), 0);
	child1(&pipex);
	i = 0;
	while (++i < argc - 4)
		child(&pipex, i);
	pipex.pid[i] = fork();
	has_error_of_pid(&pipex, pipex.pid[argc - 4]);
	child2(&pipex);
	close(pipex.pipefd[argc - 5][0]);
	waitpid(pipex.pid[argc - 4], 0, 0);
	return (finish(&pipex, 1), 0);
}
