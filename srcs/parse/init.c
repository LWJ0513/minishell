/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:36:01 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/29 20:36:54 by wonlim           ###   ########.fr       */
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

void	init_mini(t_mini *mini)
{
	ft_bzero(mini, sizeof(t_mini));
}
