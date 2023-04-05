/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:13:11 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 01:31:26 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int when_env_name(t_cmd *node, int i, int quotation_flag)
{
	int start;
	int end;
	char *replace;
	char *value;

	i++;
	start = i;
	while (node->name[i] != '\'' && node->name[i] != '\"' && node->name[i] != ' ' && node->name[i] != '\0')
	{
		i++;
	}
	end = i;

	if (quotation_flag < 1)
	{
		value = get_env(node->name, start, end);
		replace = replace_env(node->name, start - 1, end, value);
		free(node->name);
		node->name = replace;
		if (value)
			return start + ft_strlen(value) - 1;
		else
			return start - 1;
	}

	return i;
}

void when_quotation_name(t_cmd *node, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*quotation_flag = 1;
		replace = delete (node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else if (*quotation_flag == 1 && *double_quotation_flag == 0)
	{
		*quotation_flag = 0;
		replace = delete (node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else
		*i += 1;
}

void when_double_quotation_name(t_cmd *node, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*double_quotation_flag = 1;
		replace = delete (node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else if (*quotation_flag == 0 && *double_quotation_flag == 1)
	{
		*double_quotation_flag = 0;
		replace = delete (node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else
		*i += 1;
}

void replace_name(t_cmd *node, int quotation_flag, int double_quotation_flag)
{
	int i;

	i = 0;
	while (node->name[i])
	{
		if (node->name[i] == '$')
			i = when_env_name(node, i, quotation_flag);
		else if (node->name[i] == '\'')
			when_quotation_name(node, &i, &quotation_flag, &double_quotation_flag);
		else if (node->name[i] == '\"')
			when_double_quotation_name(node, &i, &quotation_flag, &double_quotation_flag);
		else
			i++;
	}
}
