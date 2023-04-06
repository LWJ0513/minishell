/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rdir_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:25:55 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 21:21:21 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_rdir *get_last_rdir_node(t_rdir *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void set_file(t_rdir *r, char *str, int *index, int *end)
{
	int i;
	int j;

	i = *index;
	if (!str[i])
	{
		r->with = 0;
		return;
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

void set_cmd_options(t_cmd *node, int index, int i, int j)
{
	t_rdir *r;
	int count;

	count = count_options(node->rdir, &index);
	if (!count)
		return;
	node->content = malloc(sizeof(char *) * (count + 1));
	if (!node->content)
		ft_error_exit("malloc error", 1);
	r = node->rdir;
	while (r)
	{
		if (r->type == -1)
		{
			if (i == index)
				node->name = r->with;
			else
				node->content[j++] = r->with;
			r->with = 0;
		}
		r = r->next;
		i++;
	}
	node->content[j] = 0;
}

int set_rdir_node(t_cmd *cmd)
{
	t_rdir *head;
	t_rdir *prev;
	t_rdir *node;
	t_rdir *next;

	node = cmd->rdir;
	while (node)
	{
		if (!node->with)
		{
			ft_printf("syntax error\n");
			g_info.last_exit_num = 258;
			return 1;
		}
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
	return 0;
}

int make_rdir_node(t_cmd *node, char *str, int i, int end)
{
	t_rdir *last_node;
	t_rdir *r;

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
		// printf("i : %d\nend : %d\n", i, end);
		set_file(r, str, &i, &end);
		// printf("%s\n", r->with);
		while (str[i] == ' ')
			i++;
	}
	set_cmd_options(node, -1, 0, 0);
	if (set_rdir_node(node))
		return 1;

	if (node->name)
		replace_name(node, 0, 0);
	replace_with(node, 0, 0);
	if (!node->content)
		return 0;
	if (!ft_strcmp(node->content[0], ""))
	{
		free(node->content[0]);
		free(node->content);
		node->content = 0;
	}
	replace_content(node, 0, 0);
	return 0;
}
