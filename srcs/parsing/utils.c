/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:50:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:27:02 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*make_node(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		printf("실패\n");
	}
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
	result = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!result)
		return 0;
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

void print_pipe(int cnt)
{
	while (cnt > 0)
	{
		if (cnt > 1)
			printf("pipe ");
		else
			printf("pipe");
		cnt--;
	}
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
