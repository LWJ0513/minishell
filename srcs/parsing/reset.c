/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:15:39 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:27:06 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void reset_list(t_list *list)
{
	list->head = 0;
	list->pid = -1;
	list->cnt_pipe = 0;
	list->cnt_cmd = 0;
}

void reset_node(t_node *node)
{
	node->result = 0;
	node->cmd = 0;
	node->next = 0;
}