/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:31:16 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:02:24 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_last_cmd_node(t_cmd *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

t_rdir	*get_last_rdir_node(t_rdir *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}
