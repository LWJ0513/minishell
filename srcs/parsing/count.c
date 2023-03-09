/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:28:37 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/09 23:44:30 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_pipe(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int count_cmd(t_list *list, int max)
{
	t_node *node;
	int i;
	int count;

	i = 0;
	count = 0;
	node = list->head;
	while (i < max)
	{
		if (node->cmd)
			count++;
		node = node->next;
		i++;
	}
	return (count);
}

int count_char(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int count_options(t_red *r, int *index)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (r)
	{
		if (r->flag == 0)
		{
			if (*index == -1)
				*index = i;
			count++;
		}
		i++;
		r = r->next;
	}
	return (count);
}
