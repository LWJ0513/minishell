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
#include <string.h>
int    ft_cd(char *str)
{
    int ret;
    char    *tmp;

    ret = -1;
    if (!strcmp(str,"") || !strcmp(str,"~") || !strcmp(str,"~/"))
    {
        ret = chdir(getenv("HOME"));
    }
    else if(!strcmp(str,"~"))
    {
        ret = chdir(getenv("HOME"));
    }
    else if(!strncmp(str,"..",2))
    {
        tmp = ft_strjoin(ft_strjoin(getcwd(0,0),"/"),str);
        ret = chdir(tmp);
        free(tmp);
    }
    else if(!strncmp(str,"./",2))
    {
        tmp =ft_strjoin(ft_strjoin(getcwd(0,0),"/"),str);
        ret = chdir(tmp);
        free(tmp);
    }
    else if (ret)
        perror("cd");
    else
    {
        ret = chdir(str);
    }
    free(str);
    return (ret);
}
