/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:33:16 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/20 16:33:19 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>

void	export(t_ms *ms)
{
	char	**env;
	int		i;

	if (ms->cmd->next && ms->cmd->next->token == NONE)
	{
		add_export(ms);
		frees(ms, ms->status);
	}
	env = convert_t_env_to_str_array(ms, NULL, 1);
	i = -1;
	while (env[++i])
	{
		ms->tmp1 = ft_strchr(env[i], '=');
		if (ms->tmp1)
		{
			*ms->tmp1 = 0;
			printf("declare -x %s=\"%s\"\n", env[i], ms->tmp1 + 1);
		}
		else
			printf("declare -x %s\n", env[i]);
	}
	ms->tmp1 = NULL;
	ft_free_malloc(env);
	frees(ms, 0);
}
