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

void    ft_export(char *str, t_mini *mini)
{
    char    **tmp;

    tmp = NULL;
    if (tmp)
        ;
    if (!str)
        ft_print_export(mini->env_exp);
    else
    {
        tmp =ft_split(str,'=');
        Insert(mini->env, tmp, tmp[0], tmp[1]);
        Insert(mini->env_exp, tmp, tmp[0], tmp[1]);

        ft_sort_envp(mini->env_exp);
    }
}