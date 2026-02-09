/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:02 by eates             #+#    #+#             */
/*   Updated: 2024/01/20 14:13:02 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>

char	*get_env(t_ms *ms, char *key)
{
	t_env	*tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	unset(t_ms *ms)
{
	t_cmd	*tmp;

	tmp = ms->cmd->next;
	while (tmp && tmp->token != PIPE)
	{
		if (control(tmp->value, 1))
			ms->status = 1;
		else
			delete_env(ms, tmp->value);
		tmp = tmp->next;
	}
}

void	env(t_ms *ms)
{
	t_env	*env;

	if (ms->cmd->next && ms->cmd->next->token != PIPE)
		return (write_error("env: ", ms->cmd->next->value,
				": No such file or directory"), frees(ms, 127));
	env = ms->env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	frees(ms, 0);
}
