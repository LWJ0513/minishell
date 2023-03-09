/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:05:21 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/10 00:54:18 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmp_builtin(char *cmd)
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

void	search_path(char **path, t_node *node)
{
	char	*direction;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		direction = ft_strjoin(tmp, node->cmd);
		free(tmp);
		if (!access(direction, F_OK))
		{
			free(node->cmd);
			node->cmd = direction;
			return ;
		}
		free(direction);
		i++;
	}
}

void	valid_cmd(char **path, t_list *list)
{
	t_node	*node;

	node = list->head;
	while (node)
	{
		if (cmp_builtin(node->cmd))
			search_path(path, node);
		node = node->next;
	}
}
