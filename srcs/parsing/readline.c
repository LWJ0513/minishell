/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:37:48 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/10 00:51:57 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pipe(int cnt)
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

void	ft_readline(t_mini *mini, t_list *list)
{
	if (!mini->pipe_flag)
		mini->line = readline("minishell $ ");
	else
	{
		print_pipe(list->cnt_cmd);
		mini->line2 = readline("> ");
		mini->str = ft_strjoin(mini->line, "\n");
		free(mini->line);
		mini->line = ft_strjoin(mini->str, mini->line2);
		free(mini->line2);
		free(mini->str);
	}
}
