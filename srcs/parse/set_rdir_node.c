/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rdir_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:25:55 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:38:42 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_file(t_rdir *r, char *str, int *index, int *end)
{
	int	i;
	int	j;

	i = *index;
	if (!str[i])
	{
		r->with = 0;
		return ;
	}
	r->with = malloc((int)(*end - i + 1));
	if (!r->with)
		ft_error_exit("malloc error", 1);
	j = 0;
	while (i < *end)
	{
		r->with[j] = str[i];
		j++;
		i++;
	}
	r->with[j] = '\0';
	*index = *end;
}

int	set_rdir_node(t_cmd *cmd)
{
	t_rdir	*head;
	t_rdir	*prev;
	t_rdir	*node;
	t_rdir	*next;

	node = cmd->rdir;
	while (node)
	{
		head = cmd->rdir;
		next = node->next;
		if (node->type == -1)
		{
			if (node == head)
				cmd->rdir = next;
			else
				prev->next = next;
			free(node);
		}
		else
			prev = node;
		node = next;
	}
	return (0);
}

void	malloc_rdir_node(t_cmd *node, char *str, int i, int end)
{
	t_rdir	*last_node;
	t_rdir	*r;

	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		r = malloc(sizeof(t_rdir));
		if (!r)
			ft_error_exit("malloc error", 1);
		ft_bzero(r, sizeof(t_rdir));
		if (!node->rdir)
			node->rdir = r;
		else
		{
			last_node = get_last_rdir_node(node->rdir);
			last_node->next = r;
		}
		r->type = check_redirection(str, &i, &end);
		set_file(r, str, &i, &end);
		while (str[i] && str[i] == ' ')
			i++;
	}
}

int	make_rdir_node(t_cmd *node, char *str)
{
	malloc_rdir_node(node, str, 0, 0);
	set_cmd_options(node, -1);
	set_rdir_node(node);
	if (check_exception(node))
		return (1);
	if (node->name)
		replace_name(node, 0, 0);
	replace_with(node, 0, 0);
	if (!node->content)
		return (0);
	if (!ft_strcmp(node->content[0], ""))
	{
		free(node->content[0]);
		free(node->content);
		node->content = 0;
	}
	replace_content(node, 0, 0);
	return (0);
}
