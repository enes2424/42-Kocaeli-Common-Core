/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakbulak <oakbulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:20:04 by eates             #+#    #+#             */
/*   Updated: 2024/01/20 14:13:34 by oakbulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_env	*create_env(char **ev, int i, int j)
{
	t_env	*env;
	t_env	*tmp;

	if (!ev[0])
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		exit(1);
	tmp = env;
	while (ev[++i])
	{
		j = ft_strchr(ev[i], '=') - ev[i];
		tmp->key = ft_substr(ev[i], 0, j);
		tmp->value = ft_substr(ev[i], j + 1, ft_strlen(ev[i]));
		if (!tmp->value || !tmp->key)
			free_env(env, 1);
		if (ev[i + 1])
		{
			tmp->next = ft_calloc(1, sizeof(t_env));
			if (!tmp->next)
				free_env(env, 1);
			tmp = tmp->next;
		}
	}
	return (env);
}

int	edit_env(t_ms *ms, t_env *env, char **ev, int i)
{
	if (env->value)
	{
		ms->tmp1 = ft_strjoin(env->key, "=");
		if (!ms->tmp1)
			frees2(ev, NULL, ms);
		ev[i] = ft_strjoin(ms->tmp1, env->value);
		ft_free((void **)&ms->tmp1, 0);
		if (!ev[i])
			frees2(ev, NULL, ms);
		return (1);
	}
	return (0);
}

char	**convert_t_env_to_str_array2(t_ms *ms, char **cmd,
	char **ev, int status)
{
	t_env	*env;
	int		i;

	env = ms->env;
	i = -1;
	while (env)
	{
		if (edit_env(ms, env, ev, ++i))
			;
		else if (status)
		{
			ev[i] = ft_strdup(env->key);
			if (!ev[i])
				frees2(ev, cmd, ms);
		}
		else
			i--;
		env = env->next;
	}
	if (status)
		return (sort(ev));
	return (free_env(ms->env, 0), ms->env = NULL, ev);
}

char	**convert_t_env_to_str_array(t_ms *ms, char **cmd, int status)
{
	char	**ev;
	t_env	*env;
	int		size;

	env = ms->env;
	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	ev = ft_calloc((size + 1), sizeof(char *));
	if (!ev)
	{
		if (cmd)
			ft_free_malloc(cmd);
		frees(ms, 1);
	}
	return (convert_t_env_to_str_array2(ms, cmd, ev, status));
}
