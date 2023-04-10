/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:38:04 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 20:28:15 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_sigint_handler(int signo)
{
	if (signo == SIGINT)
		exit(1);
	ft_putendl_fd("", STDOUT_FILENO);
	exit(0);
}

void	f(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_info.last_exit_num = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal(void)
{
	ignore_signal();
	signal(SIGINT, f);
	signal(SIGQUIT, f);
}
