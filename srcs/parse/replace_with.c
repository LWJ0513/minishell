/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:11:24 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 20:30:24 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int when_env_with(t_rdir *r, int i, int quotation_flag)
{
	int start;
	int end;
	char *replace;
	char *value;

	i++;
	start = i;
	while (r->with[i] != '\'' && r->with[i] != '\"' && r->with[i] != ' ' && r->with[i] != '\0')
	{
		i++;
	}
	end = i;

	if (quotation_flag < 1)
	{
		value = get_env(r->with, start, end);
		replace = replace_env(r->with, start - 1, end, value);
		free(r->with);
		r->with = replace;
		if (value)
			return start + ft_strlen(value) - 1;
		else
			return start - 1;
	}

	return i;
}

void when_quotation_with(t_rdir *node, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*quotation_flag = 1;
		replace = delete (node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else if (*quotation_flag == 1 && *double_quotation_flag == 0)
	{
		*quotation_flag = 0;
		replace = delete (node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else
		*i += 1;
}

void when_double_quotation_with(t_rdir *node, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*double_quotation_flag = 1;
		replace = delete (node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else if (*quotation_flag == 0 && *double_quotation_flag == 1)
	{
		*double_quotation_flag = 0;
		replace = delete (node->with, *i);
		free(node->with);
		node->with = replace;
	}
	else
		*i += 1;
}

void replace_with(t_cmd *node, int quotation_flag, int double_quotation_flag)
{
	int i;
	t_rdir *r;

	i = 0;
	r = node->rdir;
	while (r)
	{
		while (r->with[i])
		{
			if (r->with[i] == '$')
				i = when_env_with(r, i, quotation_flag);
			else if (r->with[i] == '\'')
				when_quotation_with(r, &i, &quotation_flag, &double_quotation_flag);
			else if (r->with[i] == '\"')
				when_double_quotation_with(r, &i, &quotation_flag, &double_quotation_flag);
			else
				i++;
		}
		r = r->next;
	}
}
