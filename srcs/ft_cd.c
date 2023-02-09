/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:51:37 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 17:57:41 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_cd(char *str)
{
    int ret;

    ret = chdir(str);
    if (ret)
        perror("cd");
    else
        chdir(str);
    free(str);
}
