/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:22:57 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:26:39 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_echo(t_node *tmp)
{
    unsigned long i;
    if (!ft_strcmp(tmp->option[1], "-n"))
    {
        i = 2;
        while (i < ft_strlen(tmp->option[0]) - 1)
        {
            printf("%s ",tmp->option[i++]);
        }
        printf("%s",tmp->option[i]);
    }
    else
    {
        i = 1;
        while (i < ft_strlen(tmp->option[0]) - 1)
        {
            printf("%s ",tmp->option[i++]);
        }
        printf("%s\n",tmp->option[i]);
    }
}