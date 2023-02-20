/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:50:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/20 17:42:16 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*make_node(char *str)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	reset_node(node);
	node->cmd = ft_split(str, ' ');
	return (node);
}

t_node	*get_last_node(t_node *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

char *eliminate(char *str, char c)
{
	int i;
	int j;
	int count;
	char *result;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	result = malloc(sizeof(char) * ft_strlen(str) - count + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != c)
		{
			result[j] = str[i];
			j++;
		}
	}
	result[j] = 0;
	return result;
}
