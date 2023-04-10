/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:18:52 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:46:51 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*replace_env(char *str, int start, int end, char *value)
{
	char	*replace;
	int		i;
	int		j;
	int		k;

	if (!value)
		return (0);
	replace = malloc(ft_strlen(str) - (end - start) + ft_strlen(value) + 1);
	i = 0;
	j = 0;
	while (i < start)
		replace[j++] = str[i++];
	if (value)
	{
		k = 0;
		while (value[k])
			replace[j++] = value[k++];
		i = end;
	}
	else
		i = end;
	while (i < (int)ft_strlen(str))
		replace[j++] = str[i++];
	replace[j] = '\0';
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

char	*get_env(char *str, int start, int end)
{
	char	*env;
	int		j;

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
		return (ft_itoa(g_info.last_exit_num));
	}
	return (cmpenv(env));
}
