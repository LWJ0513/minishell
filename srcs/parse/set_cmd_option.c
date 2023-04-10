/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:12:58 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:58:13 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	when_count_one(t_cmd *node, t_rdir *r, int index, int i)
{
	node->content = 0;
	while (r)
	{
		if (r->type == -1 && i == index)
		{
			node->name = r->with;
			r->with = 0;
			return ;
		}
		i++;
	}
}

void	when_count_over_one(t_cmd *node, t_rdir *r, int index, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->content = malloc(sizeof(char *) * (count + 1));
	if (!node->content)
		ft_error_exit("malloc error", 1);
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

void	set_cmd_options(t_cmd *node, int index)
{
	int		count;

	count = count_options(node->rdir, &index);
	if (!count)
		return ;
	if (count == 1)
		when_count_one(node, node->rdir, index, 0);
	else
		when_count_over_one(node, node->rdir, index, count);
}
