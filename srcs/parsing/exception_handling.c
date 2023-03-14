/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:35:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/14 15:57:35 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_last_pipe(char *str)
{
	int	size;

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

int	check_redirection_error(t_node *node, t_red	*r, int i)
{
	while (node)
	{
		r = node->r_node;
		while (r)
		{
			i = 0;
			while (r->file && r->file[i])
			{
				if (r->file[i] == '>' || r->file[i] == '<')
				{
					if (r->file[i] == '>')
						ft_printf(\
						"bash: syntax error near unexpected token `>'\n");
					if (r->file[i] == '<')
						ft_printf(\
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

int	exception_handling(char *str, t_list *list, t_mini *mini)
{
	if (check_last_pipe(str) && list->cnt_pipe == list->cnt_cmd)
	{
		mini->pipe_flag++;
		free_list(list, list->cnt_cmd);
		list->head = 0;
		free(mini->line2);
		return (1);
	}
	if (mini->cnt_node != list->cnt_cmd || list->cnt_pipe + 1 != list->cnt_cmd)
	{
		add_history(mini->line2);
		printf("Syntax error !\n");
		free(mini->line);
		free(mini->line2);
		free_list(list, list->cnt_cmd);
		return (1);
	}
	if (check_redirection_error(list->head, 0, 0))
		return (1);
	return (0);
}
