/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:21:51 by oakbulak          #+#    #+#             */
/*   Updated: 2024/01/20 18:46:20 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	ft_signal(int x)
{
	if (x == SIGINT && !g_sig_control)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (x == SIGINT)
	{
		if (g_sig_control == 4)
			exit(1);
		else
			printf("\n");
		g_sig_control = 2;
	}
	else if (x == EOF)
		;
	else if (x == SIGQUIT && g_sig_control == 1)
	{
		printf("Quit: 3\n");
		g_sig_control = 3;
	}
	else if (x == SIGQUIT)
		return ;
}

void	sigcontrol(void)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(EOF, ft_signal);
}
