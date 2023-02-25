/* ************************************************************************** */
/*                                                             `               */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:40:19 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 14:47:54 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int main_sub(t_mini *mini, t_list *list, char **envp)
{
	mini->line2 = eliminate(mini->line, '\n'); // malloc
	if (!mini->line2)
	{
		free(mini->line);
		exit(0);	// todo 바로 종료?
	}
	mini->str = cut_front(mini->line2);
	if (!mini->str || mini->str[0] == '\0')
	{
		free(mini->line);
		free(mini->line2);
		return (1);
	}
	list->cnt_pipe = count_pipe(mini->str);
	set_node(ft_split(mini->str, '|'), list, mini);
	if (exception_handling(mini->str, list, mini))
		return (1);
	valid_cmd(mini->path, list);
	execute_command_2(list, mini, envp);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_list list;
	t_mini mini;

	if (argc != 1 || !argv)
		exit(0);
	init_mini(&mini);
	init_list(&list);
	mini.env = envp_init(envp);
	mini.env_exp = envp_exp_init(envp);
	mini.path = ft_split(get_path(mini.env), ':'); // malloc
	while (1)
	{
		ft_readline(&mini, &list);
		if (mini.line)
		{
			if (main_sub(&mini, &list, envp))
				continue;
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;
		history(&mini);
		free_main(&mini, &list);
		mini.pipe_flag = 0;
		init_list(&list);
	}
	// todo env free
	// todo path free해줘야할..걸?
}
