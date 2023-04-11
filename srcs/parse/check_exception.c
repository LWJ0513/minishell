/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:30:21 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:32:22 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exception(t_cmd *node)
{
	t_rdir	*r;

	r = node->rdir;
	while (r)
	{
		if (!r->with && r->type != -1)
		{
			syntax_error();
			free_cmd(node, 1);
			return (1);
		}
		r = r->next;
	}
	return (check_redirection_error(node, node->rdir, 0));
}
