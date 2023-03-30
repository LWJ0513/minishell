/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:35:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/30 19:13:07 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_last_pipe(char *str)
{
	int size;

	size = ft_strlen(str);
	while (size > 0)
	{
		if (str[size - 1] == '|')
			return (1);
		if (str[size - 1] == ' ')
			size--;
		else
			return (0);
	}
	return (0);
}

int check_redirection_error(t_cmd *node, t_rdir *r, int i)
{
	while (node)
	{
		r = node->rdir;
		while (r)
		{
			i = 0;
			while (r->with && r->with[i])
			{
				if (r->with[i] == '>' || r->with[i] == '<')
				{
					if (r->with[i] == '>')
						ft_printf(
							"bash: syntax error near unexpected token `>'\n");
					if (r->with[i] == '<')
						ft_printf(
							"bash: syntax error near unexpected token `<'\n");
					return (1);
				}
				i++;
			}
			r = r->next;
		}
		node = node->next;
	}
	return (0);
}

int exception_handling(char *str, t_mini *mini)
{
	if (check_last_pipe(str) && mini->cnt_pipe == mini->cnt_cmd)
	{
		ft_printf("마지막이 파이프고 파이프 갯수랑 명령어 갯수가 똗ㄱ같음\n");
		mini->pipe_flag++;
		free_cmd(mini->cmds, mini->cnt_cmd);
		mini->cmds = 0;
		free(mini->line2);
		return (1);
	}
	// if (mini->cnt_node != mini->cnt_cmd || mini->cnt_pipe + 1 != mini->cnt_cmd)
	// {
	// 	ft_printf("노드 갯수랑 명령어 갯수가 다르거나 || 파이프개수+1이랑 명령어 개수가 다를 때\n");
	// 	add_history(mini->line2);
	// 	printf("Syntax error !\n");
	// 	free(mini->line);
	// 	free(mini->line2);
	// 	free_cmd(mini->cmds, mini->cnt_cmd);
	// 	mini->cmds = 0;
	// 	return (1);
	// }
	if (check_redirection_error(mini->cmds, 0, 0))
	{
		free_cmd(mini->cmds, mini->cnt_cmd);
		mini->cmds = 0;
		return (1);
	}
	return (0);
}
