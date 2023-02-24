/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:51:37 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:25:31 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_cd(char *str, t_envp *envp)
{
    int ret;
    char *tmp;
    if (!envp)
		exit(0);

    ret = -1000;
    if (!str)
    {
        ret = chdir(getenv("HOME"));   
    }
    else if (!ft_strcmp(str,"~") || !ft_strcmp(str,"~/"))
    {
        ret = chdir(getenv("HOME"));
    }
    else if (!ft_strcmp(str, "~"))
    {
        ret = chdir(getenv("HOME"));
    }
    else if (!ft_strncmp(str, "..", 2))
    {
        tmp = ft_strjoin(ft_strjoin(getcwd(0, 0), "/"), str);
        ret = chdir(tmp);
        free(tmp);
    }
    else if (!ft_strncmp(str, "./", 2))
    {
        tmp = ft_strjoin(ft_strjoin(getcwd(0, 0), "/"), str);
        ret = chdir(tmp);
        free(tmp);
    }
    else if (ret==-1000)
    {
        ret = chdir(str);
    }
    else if (ret)
    {
        perror("cd");
    }
    free(str);
    return (ret);
}
