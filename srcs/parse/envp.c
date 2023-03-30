/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:25:42 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/30 19:07:19 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_envp(char **envp)
{
	char **split;
	int i;
	t_env *node;
	t_env *last;

	i = 0;
	last = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		node = malloc(sizeof(t_env));
		if (!node)
			ft_error_exit("malloc error", 1);
		node->key = split[0];
		node->value = split[1];
		node->next = 0;
		free(split);
		if (!last)
			g_info.env_lst = node;
		else
			last->next = node;
		last = node;
		node = 0;
		i++;
	}
}
