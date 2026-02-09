/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:13:55 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/22 15:10:08 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"

void	create_pwd(t_ms *ms)
{
	if_error_frees(ms, ms->tmp2, 1);
	ms->name = ft_strjoin("\033[0;32meates&oakbulak:\033[0;34m",
			ms->tmp2);
	ft_free((void **)&ms->tmp2, 0);
	if_error_frees(ms, ms->name, 1);
	ms->tmp1 = ms->name;
	ms->name = ft_strjoin(ms->name, "$> \033[0;36m");
	if_error_frees(ms, ms->name, 1);
	ft_free((void **)&ms->tmp1, 0);
}

void	create_pwd_and_name_and_home(t_ms *ms)
{
	ft_free((void **)&ms->pwd, 0);
	ms->pwd = getcwd(NULL, 0);
	if_error_frees(ms, ms->pwd, 1);
	ft_free((void **)&ms->home, 0);
	ms->home = get_env(ms, "HOME");
	if (!ms->home)
	{
		ms->home = ft_strdup("/Users/eates");
		if_error_frees(ms, ms->home, 1);
	}
	if (!ft_strncmp(ms->pwd, ms->home, ft_strlen(ms->home)))
	{
		ms->tmp1 = ft_substr(ms->pwd, ft_strlen(ms->home), ft_strlen(ms->pwd));
		if_error_frees(ms, ms->tmp1, 1);
		ms->tmp2 = ft_strjoin("~", ms->tmp1);
		ft_free((void **)&ms->tmp1, 0);
	}
	else
		ms->tmp2 = ft_strdup(ms->pwd);
	create_pwd(ms);
}
