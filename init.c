/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:18:06 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/25 12:26:25 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	init2(t_ms *ms)
{
	delete_env(ms, "OLDPWD");
	set_env(ms, "OLDPWD");
	ms->tmp1 = ft_strjoin("PWD=", ms->pwd);
	set_env(ms, ms->tmp1);
	ft_free((void **)&(ms->tmp1), 0);
	ms->tmp1 = get_env(ms, "SHLVL");
	if (ms->tmp1)
	{
		ms->tmp2 = ft_itoa(ft_atoi(ms->tmp1) + 1);
		ft_free((void **)&(ms->tmp1), 0);
		ms->tmp1 = ft_strjoin("SHLVL=", ms->tmp2);
		ft_free((void **)&(ms->tmp2), 0);
	}
	else
		ms->tmp1 = ft_strjoin("SHLVL=", "1");
	set_env(ms, ms->tmp1);
	ft_free((void **)&(ms->tmp1), 0);
	ms->num_of_pipe = 0;
	dup2(0, STD_IN);
	dup2(1, STD_OUT);
}

void	init(t_ms *ms, char **ev)
{
	ms->env = create_env(ev, -1, 0);
	ms->status = 0;
	ms->cmd = NULL;
	ms->main_cmd = NULL;
	ms->tmp2 = NULL;
	ms->tmp3 = NULL;
	ms->name = NULL;
	ms->pwd = getcwd(NULL, 0);
	if_error_frees(ms, ms->pwd, 1);
	ms->home = get_env(ms, "HOME");
	if (!ms->home)
	{
		ms->home = ft_strdup("/Users/eates");
		if_error_frees(ms, ms->home, 1);
	}
	ms->path = NULL;
	ms->convert_str = NULL;
	ms->heredocs = NULL;
	ms->is_prev_token_heredoc = 0;
	init2(ms);
}
