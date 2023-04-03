/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:18:52 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/03 14:21:38 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_env(t_env *node)
{
	int i;

	i = 0;
	if (node)
	{
		while (node->value[i])
		{
			i++;
		}
	}

	return i;
}

char *replace_env(char *str, int start, int end, t_env *node)
{
	int i;
	int j;
	int k;
	int env_len;
	char *replace;

	if (!node)
		start -= 1;

	env_len = count_env(node);

	replace = malloc(ft_strlen(str) - (end - start) + env_len + 1);
	i = 0;
	j = 0;
	while (i < start)
	{
		replace[j] = str[i];
		i++;
		j++;
	}
	if (node)
	{
		k = 0;
		while (node->value[k])
		{
			replace[j] = node->value[k];
			k++;
			j++;
		}
		i = end;
	}
	else
	{
		i = end;
	}
	while (i < (int)ft_strlen(str))
	{
		replace[j] = str[i];
		j++;
		i++;
	}
	replace[j] = '\0';
	free(node);
	return replace;
}

t_env *cmpenv(char *env)
{
	t_env *node;

	node = g_info.env_lst;

	while (node)
	{
		if (!ft_strcmp(node->key, env))
		{
			return node;
		}
		node = node->next;
	}
	free(env);
	return 0;
}

t_env *get_env(char *str, int start, int end)
{
	t_env *node;
	char *env;
	int j;

	env = malloc(end - start + 1); // malloc

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
		node = malloc(sizeof(t_env));
		node->key = "?";
		node->value = ft_itoa(g_info.last_exit_num);
		return (node);
	}
	return cmpenv(env);
}