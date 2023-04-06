/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:36:01 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/06 17:44:34 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	init_node(t_node *node)
// {
// 	ft_bzero(node, sizeof(t_node));
// }

// void	init_list(t_list *list)
// {
// 	ft_bzero(list, sizeof(t_list));
// 	list->pid = -1;
// }

void init_mini(t_mini *mini)
{
 	ft_bzero(mini, sizeof(t_mini));

	// mini->cmds = 0;
	// mini->pipe_flag = 0;
	// mini->cnt_pipe = 0;
	// mini->cnt_cmd = 0;
	// mini->cnt_node = 0;
	// mini->line = 0;
	// mini->line2 = 0;
	// mini->str = 0;
}
