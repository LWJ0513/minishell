/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:11:24 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:46:29 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	when_with_env(t_rdir *r, int i, int q_flag, int dq_flag)
{
	t_val	v;

	i++;
	v.start = i;
	while (r->with[i] != '\'' && r->with[i] != '\"' \
	&& r->with[i] != ' ' && r->with[i] != '\0')
		i++;
	v.end = i;
	if (q_flag < 1)
	{
		v.value = get_env(r->with, v.start, v.end, &v);
		v.replace = replace_env(r->with, v.start - 1, &v, dq_flag);
		free(r->with);
		r->with = v.replace;
		v.len = ft_strlen(v.value);
		if (!v.value)
			return (v.start - 1);
		if (v.flag)
			free(v.value);
		return (v.start + v.len - 1);
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
				i = when_with_env(r, i, q_flag, dq_flag);
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
