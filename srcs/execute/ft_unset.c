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

void ft_unset(char *str, t_mini *mini)
{
    t_e_node *tmp;

    if (str==NULL)
    {
        return ;
    }
    tmp = mini->env->head;
    while(tmp)
    {
        if (!ft_strcmp(tmp->key, str))
        {
            // printf("key : %s\n",tmp->key);
            tmp->prev->next=tmp->next;
            tmp->next->prev=tmp->prev;
            free(tmp);
        }
        tmp = tmp->next;
    }
    tmp = mini->env_exp->head;
    while(tmp)
    {
        if (!ft_strcmp(tmp->key, str))
        {
            // printf("key : %s\n",tmp->key);
            tmp->prev->next=tmp->next;
            tmp->next->prev=tmp->prev;
            free(tmp);
        }
        tmp = tmp->next;
    };
}