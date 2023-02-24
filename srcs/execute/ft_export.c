/* ************************************************************************** */
/*                                                             `               */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:40:19 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 14:47:54 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_export(char *str, t_envp *envp)
{
    char    **tmp;

    tmp = NULL;
    if (tmp)
        ;
    if (!str)
        ft_print_export(envp);
    else
    {
        tmp =ft_split(str,'=');
        Insert(envp, tmp, tmp[0], tmp[1]);
        ft_sort_envp(envp);
    }
}