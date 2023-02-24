/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:36:01 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/25 00:36:34 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_node(t_node *node)
{
	node->result = 0;
	node->cmd = 0;
	node->next = 0;
}

void init_list(t_list *list)
{
	list->head = 0;
	list->pid = -1;
	list->cnt_pipe = 0;
	list->cnt_cmd = 0;
}

void init_mini(t_mini *mini)
{
	mini->pipe_flag = 0;
	mini->cnt_node = 0;
	mini->str = 0;
	mini->line = 0;
	mini->line2 = 0;
	mini->env = 0;
	mini->path = 0;
}
