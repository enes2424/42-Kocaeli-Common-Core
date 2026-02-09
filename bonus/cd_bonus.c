/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:15:29 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/19 17:05:19 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include "../libft/libft.h"

static void	cd_error(t_ms *ms, int ctrl, int status)
{
	if (ctrl)
	{
		write(2, "/usr/bin/", 10);
		write(2, ms->cmd->value, ft_strlen(ms->cmd->value));
		write(2, ": line 4: ", 11);
	}
	else
		write(2, "minishell: ", 12);
	write(2, "cd: ", 5);
	write(2, ms->tmp1, ft_strlen(ms->tmp1));
	if (status)
		write(2, ": No such file or directory\n", 29);
	else
		write(2, ": Not a directory\n", 19);
}

int	control_cd(t_ms *ms, int ctrl)
{
	DIR		*dir;

	if (!access(ms->tmp1, F_OK))
	{
		dir = opendir(ms->tmp1);
		if (dir)
			closedir(dir);
		else
			return (cd_error(ms, ctrl, 0), 1);
	}
	else
		return (cd_error(ms, ctrl, 1), 1);
	return (0);
}

void	cd_pwd(t_ms *ms)
{
	chdir(ms->tmp1);
	ms->tmp2 = ft_strjoin("OLDPWD=", ms->pwd);
	if_error_frees(ms, ms->tmp2, 1);
	set_env(ms, ms->tmp2);
	ft_free((void **)&ms->tmp2, 0);
	ft_free((void **)&ms->pwd, 0);
	ms->pwd = getcwd(NULL, 0);
	if_error_frees(ms, ms->pwd, 1);
	ms->tmp2 = ft_strjoin("PWD=", ms->pwd);
	if_error_frees(ms, ms->tmp2, 1);
	set_env(ms, ms->tmp2);
	ft_free((void **)&ms->tmp2, 0);
}

void	cd(t_ms *ms)
{
	int	can_work;

	ms->status = 0;
	can_work = ms->cmd->value[0] == 'c' && ms->cmd->value[1] == 'd';
	if (!ms->cmd->next || ms->cmd->next->token != NONE)
		ms->tmp1 = ft_strdup(ms->home);
	else if (ms->cmd->next->value[0] == '~'
		&& (ms->cmd->next->value[1] == '/' || !ms->cmd->next->value[1]))
		ms->tmp1 = ft_strjoin(ms->home, ms->cmd->next->value + 1);
	else
		ms->tmp1 = ft_strdup(ms->cmd->next->value);
	if_error_frees(ms, ms->tmp1, 1);
	if (control_cd(ms, !can_work))
		ms->status = 1;
	if (!ms->status && can_work)
		cd_pwd(ms);
	ft_free((void **)&ms->tmp1, 0);
}
