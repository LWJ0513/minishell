/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:11:24 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 20:40:31 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	when_with_env(t_rdir *r, int i, int q_flag)
{
	char	*replace;
	char	*value;
	int		start;
	int		end;

	i++;
	start = i;
	while (r->with[i] != '\'' && r->with[i] != '\"' \
	&& r->with[i] != ' ' && r->with[i] != '\0')
		i++;
	end = i;
	if (q_flag < 1)
	{
		value = get_env(r->with, start, end);
		replace = replace_env(r->with, start - 1, end, value);
		free(r->with);
		r->with = replace;
		if (value)
			return (start + ft_strlen(value) - 1);
		else
			return (start - 1);
	}
	return (i);
}

void	when_with_q(t_rdir *node, int *i, int *q_flag, int *dq_flag)
{
	char	*replace;

	if (*q_flag == 0 && *dq_flag == 0)
	{
		*q_flag = 1;
		replace = delete(node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else if (*q_flag == 1 && *dq_flag == 0)
	{
		*q_flag = 0;
		replace = delete(node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else
		*i += 1;
}

void	when_with_dq(t_rdir *node, int *i, int *q_flag, int *dq_flag)
{
	char	*replace;

	if (*q_flag == 0 && *dq_flag == 0)
	{
		*dq_flag = 1;
		replace = delete(node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else if (*q_flag == 0 && *dq_flag == 1)
	{
		*dq_flag = 0;
		replace = delete(node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else
		*i += 1;
}

void	replace_with(t_cmd *node, int q_flag, int dq_flag)
{
	t_rdir	*r;
	int		i;

	i = 0;
	r = node->rdir;
	while (r)
	{
		while (r->with[i])
		{
			if (r->with[i] == '$')
				i = when_with_env(r, i, q_flag);
			else if (r->with[i] == '\'')
				when_with_q(r, &i, &q_flag, &dq_flag);
			else if (r->with[i] == '\"')
				when_with_dq(r, &i, &q_flag, &dq_flag);
			else
				i++;
		}
		r = r->next;
	}
}
