/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_r_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:25:55 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/14 15:39:18 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_file(t_red *r, char *str, int *index, int *end)
{
	int	i;
	int	j;

	i = *index;
	r->file = malloc((int)(*end - i + 1));
	// todo 널가드
	j = 0;
	while (i < *end)
	{
		r->file[j] = str[i];
		j++;
		i++;
	}
	r->file[j] = '\0';
	*index = *end;
}

void	set_cmd_options(t_node *node, int index, int i, int j)
{
	t_red	*r;
	int		count;

	count = count_options(node->r_node, &index);
	if (!count)
		return ;
	node->option = malloc(sizeof(char *) * (count + 1));
	// todo 널가드
	r = node->r_node;
	while (r)
	{
		if (!r->flag)
		{
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

void	make_r_node(t_node *node, char *str, int i, int end)
{
	t_red	*last_node;
	t_red	*r;

	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		r = malloc(sizeof(t_red));
		// if (!r)
		// todo 널가드
		ft_bzero(r, sizeof(t_red));
		if (!node->r_node)
			node->r_node = r;
		else
		{
			last_node = get_last_r_node(node->r_node);
			last_node->next = r;
		}
		r->flag = check_redirection(str, &i, &end);
		set_file(r, str, &i, &end);
		while (str[i] == ' ')
			i++;
	}
	set_cmd_options(node, -1, 0, 0);
}
