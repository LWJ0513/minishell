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
    if (!ft_strcmp(tmp->cmd[1], "-n"))
        printf("%s",tmp->cmd[2]);
    else
        printf("%s\n",tmp->cmd[1]);
}