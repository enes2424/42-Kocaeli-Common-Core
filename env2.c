/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:20:01 by eates             #+#    #+#             */
/*   Updated: 2024/01/20 14:13:06 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	add_env(t_ms *ms, t_env *tmp, char *key, char *value)
{
	tmp = ms->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(key);
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_calloc(1, sizeof(t_env));
	if (!tmp->next)
		return (free(key), free(value), frees(ms, 1));
	tmp->next->key = key;
	tmp->next->value = value;
}

void	set_env(t_ms *ms, char *key)
{
	char	*value;

	key = ft_strdup(key);
	if_error_frees(ms, key, 1);
	value = ft_strchr(key, '=');
	if (value)
	{
		*value = 0;
		value = ft_strdup(value + 1);
		if (!value)
		{
			free(key);
			frees(ms, 1);
		}
	}
	if (!ms->env)
	{
		ms->env = ft_calloc(1, sizeof(t_env));
		if (!ms->env)
			return (free(key), free(value), frees(ms, 1));
		ms->env->key = key;
		ms->env->value = value;
		return ;
	}
	add_env(ms, ms->env, key, value);
}

void	delete_env(t_ms *ms, char *str)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = ms->env;
	if (!tmp)
		return ;
	if (!ft_strcmp(ms->env->key, str))
		return (ms->env = ms->env->next, free(tmp->value),
			free(tmp->key), free(tmp));
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, str))
			return (tmp2 = tmp->next, tmp->next = tmp->next->next,
				free(tmp2->value), free(tmp2->key), free(tmp2));
		tmp = tmp->next;
	}
}

void	add_export(t_ms *ms)
{
	t_cmd	*tmp;

	tmp = ms->cmd->next;
	while (tmp && tmp->token != PIPE)
	{
		if (control(tmp->value, 0))
			ms->status = 1;
		else
			set_env(ms, tmp->value);
		tmp = tmp->next;
	}
}
