/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:50:12 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 00:52:13 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int count_rdir(t_rdir *node)
{
	int cnt;

	cnt = 0;
	while (node)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}

void free_rdir(t_rdir *head, int cnt)
{
	t_rdir *node;
	t_rdir *next_node;

	node = head;
	while (cnt)
	{
		next_node = node->next;
		free(node->with);
		free(node);
		node = next_node;
		cnt--;
	}
}

void free_cmd(t_cmd *head, int cnt)
{
	t_cmd *node;
	t_cmd *next_node;

	node = head;
	if (!node)
		return;
	while (cnt)
	{
		next_node = node->next;
		if (node->name)
			free(node->name);
		if (node->content)
			free_split(node->content);
		if (node->rdir)
			free_rdir(node->rdir, count_rdir(node->rdir));

		free(node);
		node = next_node;
		cnt--;
	}
}

void free_main(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	// free(mini->line2);
	// free(mini->str); // ???
	if (mini->cmds)
		free_cmd(mini->cmds, mini->cnt_cmd);
}
