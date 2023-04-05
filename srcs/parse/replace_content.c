/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:16:44 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 01:12:59 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *delete(char *str, int index)
{
	char *new;
	int i;
	int j;

	new = malloc(ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != index)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';

	return new;
}

int when_env_content(t_cmd *node, int i, int j, int quotation_flag)
{
	int start;
	int end;
	char *replace;
	char *value;

	i++;
	start = i;
	while (node->content[j][i] != '\'' && node->content[j][i] != '\"' && node->content[j][i] != ' ' && node->content[j][i] != '\0')
	{
		i++;
	}
	end = i;

	if (quotation_flag < 1)
	{
		value = get_env(node->content[j], start, end);
		replace = replace_env(node->content[j], start - 1, end, value);
		free(node->content[j]);
		node->content[j] = replace;
		if (value)
			return start + ft_strlen(value) - 1;
		else
			return start - 1;
	}

	return i;
}

void when_quotation_content(t_cmd *node, int *i, int j, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*quotation_flag = 1;
		replace = delete (node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else if (*quotation_flag == 1 && *double_quotation_flag == 0)
	{
		*quotation_flag = 0;
		replace = delete (node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else
		*i += 1;
}

void when_double_quotation_content(t_cmd *node, int *i, int j, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*double_quotation_flag = 1;
		replace = delete (node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else if (*quotation_flag == 0 && *double_quotation_flag == 1)
	{
		*double_quotation_flag = 0;
		replace = delete (node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else
		*i += 1;
}

void replace_content(t_cmd *node, int quotation_flag, int double_quotation_flag)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (node->content[j])
	{
		while (node->content[j][i])
		{
			if (node->content[j][i] == '$')
				i = when_env_content(node, i, j, quotation_flag);
			else if (node->content[j][i] == '\'')
				when_quotation_content(node, &i, j, &quotation_flag, &double_quotation_flag);
			else if (node->content[j][i] == '\"')
				when_double_quotation_content(node, &i, j, &quotation_flag, &double_quotation_flag);
			else
				i++;
		}
		j++;
	}
}
