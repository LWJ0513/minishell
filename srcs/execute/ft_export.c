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

int is_key(t_mini *mini, char *key)
{
    t_e_node *tmp;

    tmp=mini->env->head;
    while(tmp)
    {
        if (!ft_strcmp(tmp->key, key))
            return (1);
        tmp=tmp->next;
    }

    return (0);
}

void    change_value(t_mini *mini, char *key, char *value)
{
    t_e_node *tmp;

    tmp = mini->env->head;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            ft_strlcpy(tmp->value, value, ft_strlen(value) + 1);
            return ;
        }
        tmp=tmp->next; 
    }
}

void    change_value_exp(t_mini *mini, char *key, char *value)
{
    t_e_node *tmp;

    tmp = mini->env_exp->head;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            ft_strlcpy(tmp->value, value, ft_strlen(value) + 1);
            return ;
        }
        tmp=tmp->next; 
    }
}

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
        if (is_key(mini, tmp[0]))
        {
            change_value(mini, tmp[0],tmp[1]);
            change_value_exp(mini, tmp[0],tmp[1]);
        }
        else
        {
            Insert(mini->env, tmp, tmp[0], tmp[1]);
            Insert(mini->env_exp, tmp, tmp[0], tmp[1]);
        }
        ft_sort_envp(mini->env_exp);
    }
}