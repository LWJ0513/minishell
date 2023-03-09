/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:35:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/10 00:57:15 by wonlim           ###   ########.fr       */
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
	return (0);
}
