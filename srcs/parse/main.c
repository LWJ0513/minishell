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

t_info g_info;

void print_test(t_mini *mini)
{
	t_cmd *cmd;
	t_rdir *r;
	cmd = mini->cmds;
	printf("------ mini -----\n");
	printf("pipe_flag = %d\n", mini->pipe_flag);
	printf("cnt_pipe = %d\n", mini->cnt_pipe);
	printf("cnt_cmd = %d\n", mini->cnt_cmd);
	printf("cnt_node = %d\n", mini->cnt_node);
	printf("line : %s\n", mini->line);
	printf("line2 : %s\n", mini->line2);
	printf("str : %s\n", mini->str);
	while (cmd)
	{
		printf("\n[cmds]-----\n");
		printf("is_heredoc : %d\n", cmd->is_heredoc);
		printf("name : %s \n", cmd->name);
		int i = 0;
		if (cmd->content)
		{
			while (cmd->content[i])
			{
				printf("content[%d] : %s\n", i, cmd->content[i]);
				i++;
			}
		}
		printf("\n[rdir]-----\n");
		r = cmd->rdir;
		while (r)
		{
			printf("type : %d\n", r->type);
			printf("with : %s\n", r->with);
			r = r->next;
		}
		cmd = cmd->next;
		printf("\n\n");
	}
}

int main_sub(t_mini *mini)
{
	mini->line2 = eliminate(mini->line, '\n'); // malloc
	mini->str = cut_front(mini->line2);
	if (!mini->str || mini->str[0] == '\0')
	{
		free(mini->line);
		free(mini->line2);
		return (1);
	}
	mini->cnt_pipe = count_pipe(mini->str);
	if (valid_quotation(mini->str))
	{
		return (1);
	}
	// printf("str : %s\n\n", mini->str);

	if (set_cmd_node(mini))
	{
		print_test(mini);

		return (1);
	}
	if (exception_handling(mini->str, mini))
		return (1);
	print_test(mini);
	execute(mini->cmds);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_mini mini;

	if (argc != 1 || !argv)
		exit(0);
	init_mini(&mini);
	init_envp(envp);
	set_terminal();
	set_signal();
	while (1)
	{
		ft_readline(&mini);
		main_sub(&mini);
		// if (main_sub(&mini))
		// 	continue;
		// else // str = NULL 이라면 (EOF, cntl +mD)
		// 	break;

		history(&mini);
		free_main(&mini);
		// mini.pipe_flag = 0;
		ft_bzero(&mini, sizeof(t_mini));
		// system("leaks minishell");
	}
}
