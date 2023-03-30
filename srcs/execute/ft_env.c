/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:01:29 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:26:52 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_cmd	*cmd)
{
	t_env	*env;

	if (cmd->content)
	{
		ft_putstr_fd(*cmd->content, 2);
		ft_putstr_fd(": No such file or diretoty\n", 2);
		g_info.last_exit_num = 127;
		return ;
	}
	env = g_info.env_lst;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	g_info.last_exit_num = 0;
}
