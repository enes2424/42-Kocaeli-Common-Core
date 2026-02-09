/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:45:09 by eates             #+#    #+#             */
/*   Updated: 2024/01/21 18:26:47 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_free(void **element, int num)
{
	return (free(*element), *element = NULL, num);
}

void	free_env(t_env *env, int status)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			ft_free((void **)&tmp->key, 0);
		if (tmp->value)
			ft_free((void **)&tmp->value, 0);
		ft_free((void **)&tmp, 0);
	}
	if (status)
		exit(1);
}

void	*free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free((void **)&tmp->value, 0);
		ft_free((void **)&tmp, 0);
	}
	return (NULL);
}

void	free_heredocs(t_ms *ms)
{
	int	i;

	i = -1;
	if (ms->heredocs)
	{
		while (ms->heredocs[++i])
		{
			if (ms->heredocs[i][1])
				close(ms->heredocs[i][0]);
			ft_free((void **)&ms->heredocs[i], 0);
		}
	}
	ft_free((void **)&(ms->heredocs), 0);
}

void	frees(t_ms *ms, int status)
{
	free_env(ms->env, 0);
	free_cmd(ms->main_cmd);
	free(ms->tmp1);
	free(ms->tmp2);
	free(ms->tmp3);
	free(ms->input);
	free(ms->name);
	free(ms->pwd);
	free(ms->home);
	free(ms->path);
	free(ms->convert_str);
	rl_clear_history();
	free_heredocs(ms);
	printf("\033[0m");
	exit(status);
}
