/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:37:48 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/29 20:38:53 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_pipe(int cnt)
{
	while (cnt > 0)
	{
		if (cnt > 1)
			printf("pipe ");
		else
			printf("pipe");
		cnt--;
	}
}

void ft_readline(t_mini *mini)
{
	if (!mini->pipe_flag)
	{
		mini->line = readline("minishell $ ");
		if (!mini->line)
		{
			g_info.last_exit_num = 0;
			exit(0);
		}
	}
	else
	{
		print_pipe(mini->cnt_cmd);
		mini->line2 = readline("> ");
		mini->str = ft_strjoin(mini->line, "\n");
		free(mini->line);
		mini->line = ft_strjoin(mini->str, mini->line2);
		free(mini->line2);
		free(mini->str);
	}
}
