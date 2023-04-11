/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_i_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:56:21 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:27:58 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_i_content(t_cmd *node, t_content_flag *f, int index)
{
	t_set_i	s;

	if (f)
		f->reset_content = 1;
	if (!node->content[1])
	{
		free(node->content);
		node->content = NULL;
		return ;
	}
	s.before = node->content;
	s.i = 0;
	while (s.before[s.i])
		s.i++;
	s.after = malloc(sizeof(char *) * s.i);
	s.i = 0;
	s.j = 0;
	while (s.j < index)
		s.after[s.i++] = s.before[s.j++];
	s.j++;
	while (s.before[s.j])
		s.after[s.i++] = s.before[s.j++];
	s.after[s.i] = s.before[s.j];
	free(s.before);
	node->content = s.after;
}
