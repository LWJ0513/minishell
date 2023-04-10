/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:13:11 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 20:43:41 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	when_name_env(t_cmd *node, int i, int q_flag)
{
	char	*replace;
	char	*value;
	int		start;
	int		end;

	i++;
	start = i;
	while (node->name[i] != '\'' && node->name[i] != '\"' \
	&& node->name[i] != ' ' && node->name[i] != '\0')
		i++;
	end = i;
	if (q_flag < 1)
	{
		value = get_env(node->name, start, end);
		replace = replace_env(node->name, start - 1, end, value);
		free(node->name);
		node->name = replace;
		if (value)
			return (start + ft_strlen(value) - 1);
		else
			return (start - 1);
	}
	return (i);
}

void	when_name_q(t_cmd *node, int *i, int *q_flag, int *dq_flag)
{
	char	*replace;

	if (*q_flag == 0 && *dq_flag == 0)
	{
		*q_flag = 1;
		replace = delete(node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else if (*q_flag == 1 && *dq_flag == 0)
	{
		*q_flag = 0;
		replace = delete(node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else
		*i += 1;
}

void	when_name_dq(t_cmd *node, int *i, int *q_flag, int *dq_flag)
{
	char	*replace;

	if (*q_flag == 0 && *dq_flag == 0)
	{
		*dq_flag = 1;
		replace = delete(node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else if (*q_flag == 0 && *dq_flag == 1)
	{
		*dq_flag = 0;
		replace = delete(node->name, *i);
		free(node->name);
		node->name = replace;
	}
	else
		*i += 1;
}

void	replace_name(t_cmd *node, int q_flag, int dq_flag)
{
	int	i;

	i = 0;
	while (node->name[i])
	{
		if (node->name[i] == '$')
			i = when_name_env(node, i, q_flag);
		else if (node->name[i] == '\'')
			when_name_q(node, &i, &q_flag, &dq_flag);
		else if (node->name[i] == '\"')
			when_name_dq(node, &i, &q_flag, &dq_flag);
		else
			i++;
	}
}
