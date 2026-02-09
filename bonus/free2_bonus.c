/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:53:48 by eates             #+#    #+#             */
/*   Updated: 2024/01/21 18:29:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "../libft/libft.h"

void	frees2(char **ev, char **cmd, t_ms *ms)
{
	if (cmd)
		ft_free_malloc(cmd);
	ft_free_malloc(ev);
	frees(ms, 1);
}

void	frees3(t_ms *ms)
{
	ft_free((void **)&ms->tmp1, 0);
	ft_free((void **)&ms->tmp2, 0);
	ft_free((void **)&ms->tmp3, 0);
	ft_free((void **)&ms->input, 0);
	ft_free((void **)&ms->name, 0);
	ft_free((void **)&ms->pwd, 0);
	ft_free((void **)&ms->home, 0);
	ft_free((void **)&ms->convert_str, 0);
	free_heredocs(ms);
}

void	frees4(t_ms *ms)
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
	free_heredocs(ms);
}

void	if_error_frees(t_ms *ms, void *elm, int status)
{
	if (!elm)
		frees(ms, status);
}
