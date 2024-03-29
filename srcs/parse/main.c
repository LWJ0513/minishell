/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:40:19 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:36:01 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_info	g_info;

int	main_sub(t_mini *mini)
{
	int	ex;

	mini->line2 = eliminate(mini->line, '\n');
	mini->str = cut_front(mini->line2);
	if (!mini->str || mini->str[0] == '\0')
	{
		free(mini->line);
		mini->line = 0;
		return (1);
	}
	if (valid_quotation(mini->str))
		return (0);
	mini->cnt_pipe = count_pipe(mini->str);
	if (set_cmd_node(mini, ft_split_pipe(mini->str), 0, 0))
		return (0);
	ex = exception_handling(mini->str, mini);
	if (ex == 1)
		return (1);
	else if (ex == 2)
		return (0);
	execute(mini->cmds);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	if (argc != 1 || !argv)
		exit(0);
	init_mini(&mini);
	init_envp(envp);
	while (1)
	{
		set_terminal();
		set_signal();
		if (ft_readline(&mini))
			continue ;
		if (main_sub(&mini))
			continue ;
		history(&mini);
		free_main(&mini);
		init_mini(&mini);
	}
}
