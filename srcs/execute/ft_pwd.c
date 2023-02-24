/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:36 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:26:10 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    ft_pwd()
{
    printf("%s\n",getcwd(0,0));
    // t_e_node *tmp;

    // tmp=envp->head;

    // while (*(tmp->next->key))
    // {
    //     // printf("tmp->key : %s\n",tmp->key);
    //     if (!ft_strcmp(tmp->key, "PWD"))
    //     {
    //         printf("%s\n",tmp->value);
    //         return (0);
    //     }
    //     tmp=tmp->next;
    // }
    return (0);
    // char *buf;
    
    // buf = getcwd(0, 0);
    // printf("%s\n", buf);
    // free(buf);
    // return (0);
}
