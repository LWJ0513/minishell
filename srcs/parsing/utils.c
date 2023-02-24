/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:50:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/25 00:50:33 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *eliminate(char *str, char c)
{
	char *result;
	int i;

	result = malloc(ft_strlen(str) - count_char(str, c) + 1);
	if (!result)
		return 0;
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			result[i] = *str;
			i++;
		}
		str++;
	}
	result[i] = 0;
	return (result);
}

char *cut_front(char *str)
{
	while (*str == ' ' || *str == '|')
	{
		if (*str == '|')
		{
			printf("zsh: parse error near `|'\n");
			return 0;
		}
		str++;
	}
	return str;
}

char *get_path(t_envp *env)
{
	t_e_node *node;
	
	node = env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, "PATH"))
			return (node->value);
		node = node->next;
	}
	return (0);
}