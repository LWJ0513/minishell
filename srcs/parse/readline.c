/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:37:48 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 23:17:44 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	when_readline_else(t_mini *mini)
{
	mini->line2 = readline("> ");
	mini->str = ft_strjoin(mini->line, "\n");
	free(mini->line);
	mini->line = ft_strjoin(mini->str, mini->line2);
	free(mini->line2);
	free(mini->str);
	mini->line2 = 0;
	mini->str = 0;
}

int	ft_readline(t_mini *mini)
{
	char	*test;

	if (!mini->pipe_flag)
	{
		mini->line = readline("minishell $ ");
		if (!mini->line)
		{
			g_info.last_exit_num = 0;
			exit(0);
		}
		test = eliminate(mini->line, ' ');
		if (!ft_strcmp(mini->line, "") || !ft_strcmp(test, ""))
		{
			free(mini->line);
			free(test);
			return (1);
		}
		free(test);
	}
	else
		when_readline_else(mini);
	return (0);
}
