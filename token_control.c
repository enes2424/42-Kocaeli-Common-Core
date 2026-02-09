/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:52:36 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/25 11:56:20 by eates            ###   ########.fr       */
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

int	ft_input(t_cmd *iter, int *fd)
{
	if (fd[0])
		close(fd[0]);
	fd[0] = open(iter->next->value, O_RDONLY);
	if (fd[0] < 0)
		return (write_error("minishell: ", iter->next->value,
				": No such file or directory"), 1);
	return (0);
}

void	ft_heredoc(t_ms *ms, int *fd)
{
	if (fd[0])
		close(fd[0]);
	dup2(ms->heredocs[ms->num_of_pipe][0], fd[0]);
}

void	ft_write(t_cmd *iter, int *fd)
{
	if (fd[1] != 1)
		close(fd[1]);
	fd[1] = open(iter->next->value, O_CREAT
			| O_APPEND | O_WRONLY, 0000644);
}

void	ft_rewrite(t_cmd *iter, int *fd)
{
	if (fd[1] != 1)
		close(fd[1]);
	fd[1] = open(iter->next->value, O_CREAT
			| O_TRUNC | O_WRONLY, 0000644);
}
