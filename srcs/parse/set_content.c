/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:47:49 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:07:59 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_content(t_cmd *node, t_content_flag *f)
{
	char	**before;
	char	**after;
	int		i;
	int		j;

	if (f)
		f->reset_content = 1;
	if (!node->content[1])
	{
		free(node->content);
		node->content = NULL;
		return ;
	}
	before = node->content;
	i = 0;
	while (before[i])
		i++;
	after = malloc(sizeof(char *) * i);
	i = 0;
	j = 1;
	while (before[j])
		after[i++] = before[j++];
	after[i] = before[j];
	free(before);
	node->content = after;
}
