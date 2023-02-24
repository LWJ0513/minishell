/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:50:12 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 22:19:00 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void free_list(t_list *list, int cnt)
{
	t_node *node;
	int i;

	while (cnt)
	{
		node = list->head;

		i = 0;
		while (i < cnt - 1)
		{
			node = node->next;
			i++;
		}
		free_split(node->cmd);
		node->cmd = 0;
		node->next = 0;
		free(node);
		cnt--;
	}
	list->head = 0;
}

void free_main(t_mini *mini, t_list *list)
{
	free(mini->line);
	free(mini->line2);
	free_list(list, list->cnt_cmd);
}
