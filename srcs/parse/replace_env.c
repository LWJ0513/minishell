/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:18:52 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 04:37:17 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*replace_env(char *str, int start, t_val *v, int dq_flag)
{
	t_index	i;
	char	*replace;
	int		end;

	end = v->end;
	if (!v->value && !dq_flag)
		return (0);
	replace = malloc(ft_strlen(str) - (end - start) + ft_strlen(v->value) + 1);
	i.i = 0;
	i.j = 0;
	while (i.i < start)
		replace[i.j++] = str[i.i++];
	if (v->value)
	{
		i.k = 0;
		while (v->value[i.k])
			replace[i.j++] = v->value[i.k++];
		i.i = end;
	}
	else
		i.i = end;
	while (i.i < (int)ft_strlen(str))
		replace[i.j++] = str[i.i++];
	replace[i.j] = '\0';
	return (replace);
}

char	*cmpenv(char *env)
{
	t_env	*node;

	node = g_info.env_lst;
	while (node)
	{
		if (!ft_strcmp(node->key, env))
		{
			free(env);
			return (node->value);
		}
		node = node->next;
	}
	free(env);
	return (0);
}

char	*get_env(char *str, int start, int end, t_val *v)
{
	char	*env;
	int		j;

	v->flag = 0;
	env = malloc(end - start + 1);
	j = 0;
	while (start < end)
	{
		env[j] = str[start];
		j++;
		start++;
	}
	env[j] = '\0';
	if (!ft_strcmp(env, "?"))
	{
		free(env);
		v->flag = 1;
		return (ft_itoa(g_info.last_exit_num));
	}
	return (cmpenv(env));
}
