/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:43 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:25:36 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_exit(t_node *tmp, t_list *list)
{
    if (tmp==list->head)
    {
        printf("exit\n");
        exit(0);
    }
}