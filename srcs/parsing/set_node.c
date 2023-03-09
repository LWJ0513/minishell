/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:59:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/09 23:31:16 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *get_last_node(t_node *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

t_red *get_last_r_node(t_red *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void set_cmd_options(t_node *node)
{
	t_red *r;
	int count;
	int index;
	int i;
	int j;

	index = -1;
	count = count_options(node->r_node, &index);
	if (count > 0)
	{
		node->option = malloc(sizeof(char *) * (count + 1));
		// todo 널가드
		r = node->r_node;
		i = 0;
		j = 0;
		while (r){
			if (!r->flag){
				if (i == index)
					node->cmd = r->file;
				node->option[j] = r->file;
				r->file = 0;
				j++;
			}
			r = r->next;
			i++;
		}
		node->option[j] = 0;
	}
}

t_node *make_node(char *str)
{
	t_node *node;
	t_red *r;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		printf("실패\n"); // todo
	}
	ft_bzero(node, sizeof(t_node));

	int start = 0, end = 0;
	int j;
	char *tmp;
	t_red *last_node;
	if (has_redirection(str))
	{
		int i = 0;
		while (str[i] == ' ')
			i++;

		while (str[i])
		{
			r = malloc(sizeof(t_red));
			// if (!r)
			// todo 널가드

			ft_bzero(r, sizeof(t_red));
			if (!node->r_node)
			{
				node->r_node = r;
			}
			else
			{
				last_node = get_last_r_node(node->r_node);
				last_node->next = r;
			}

			r->flag = check_redirection(str, i, &end);

			tmp = malloc(end - i + 1);
			// todo 널가드
			j = 0;
			while (i < end)
			{
				tmp[j] = str[i];
				j++;
				i++;
			}
			tmp[j] = '\0';

			r->file = tmp;

			i = end;
			while (str[i] == ' ')
				i++;
		}
		set_cmd_options(node);
	}
	else
	{
		node->option = ft_split(str, ' ');
		node->cmd = node->option[0];
	}

	return (node);
}

void set_node(char **split_pipe, t_list *list, t_mini *mini)
{
	t_node *node;
	t_node *last_node;
	int i;

	i = 0;
	while (split_pipe[i])
	{
		node = make_node(split_pipe[i]);
		if (list->head == 0)
		{
			list->head = node;
			node->prev = 0;
		}
		else
		{
			last_node = get_last_node(list->head);
			last_node->next = node;
			node->prev = last_node;
		}
		i++;
	}
	// list->cnt_cmd = count_cmd(list, i);
	free_split(split_pipe);
	mini->cnt_node = i;
}
