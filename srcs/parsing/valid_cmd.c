/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:05:21 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/25 00:50:28 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int cmp_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (0);
	if (!ft_strcmp(cmd, "export"))
		return (0);
	if (!ft_strcmp(cmd, "unset"))
		return (0);
	if (!ft_strcmp(cmd, "env"))
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

void search_path(char **path, t_node *node)
{
	char *tmp;
	char *direction;
	int i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		direction = ft_strjoin(tmp, node->cmd[0]);
		free(tmp);
		if (!access(direction, F_OK))
		{
			free(node->cmd[0]);
			node->cmd[0] = direction;
			return;
		}
		free(direction);
		i++;
	}
}

void valid_cmd(char **path, t_list *list)
{
	t_node *node;
	
	node = list->head;
	while (node)
	{
		if (cmp_builtin(node->cmd[0]))
			search_path(path, node);
		node = node->next;
	}
}
