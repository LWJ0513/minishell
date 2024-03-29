/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:27:09 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:27:22 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	env_free(t_env *env)
{	
	t_env	*del_temp;

	del_temp = env->next;
	env->next = del_temp->next;
	free(del_temp->key);
	free(del_temp->value);
	free(del_temp);
	g_info.last_exit_num = 0;
}

static void	last_env_free(t_env *env)
{
	t_env	*del_temp;

	del_temp = env->next;
	env->next = 0;
	free(del_temp->key);
	free(del_temp->value);
	free(del_temp);
	g_info.last_exit_num = 0;
}

static void	first_env_free(t_env *env)
{
	g_info.env_lst = env->next;
	free(env->key);
	free(env->value);
	free(env);
	g_info.last_exit_num = 0;
}

void	ft_unset(t_cmd *cmd)
{
	t_env	*env_temp;
	char	**str;

	str = cmd->content;
	while (*str && g_info.env_lst)
	{
		env_temp = g_info.env_lst;
		if (env_temp && ft_strcmp(env_temp->key, *cmd->content) == 0)
			first_env_free(env_temp);
		else
		{
			while (env_temp->next && ft_strcmp(env_temp->next->key, *str))
				env_temp = env_temp->next;
			if (!env_temp->next)
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				g_info.last_exit_num = 1;
			}
			else if (env_temp->next->next == 0)
				last_env_free(env_temp);
			else
				env_free(env_temp);
		}
		str++;
	}
}
