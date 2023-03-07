/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:59:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/07 15:34:49 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*make_node(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		printf("실패\n");	// todo
	}
	init_node(node);
	node->cmd = ft_split(str, ' ');
	return (node);
}

t_node	*get_last_node(t_node *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void set_node(char **split_pipe, t_list *list, t_mini *mini)
{
	t_node *node;
	t_node *last_node;
	int i;

	i = 0;
	while (split_pipe[i])
	{
		node = make_node(split_pipe[i]);
		if (list->head == 0)
		{
			list->head = node;
			node->prev = 0;
		}
		else
		{
			last_node = get_last_node(list->head);
			last_node->next = node;
			node->prev = last_node;
		}
		i++;
	}
	list->cnt_cmd = count_cmd(list, i);
	free_split(split_pipe);
	mini->cnt_node = i;
}
