/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:51 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:35:45 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_env(t_envp *envp)
{
    t_e_node *tmp;

    tmp = envp->head;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp=tmp->next;
    }
}