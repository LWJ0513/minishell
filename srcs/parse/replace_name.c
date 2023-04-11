/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:13:11 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:45:45 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	when_name_env(t_cmd *node, int i, int q_flag, int dq_flag)
{
	t_val	v;

	i++;
	v.start = i;
	while (node->name[i] != '\'' && node->name[i] != '\"' \
	&& node->name[i] != ' ' && node->name[i] != '\0')
		i++;
	v.end = i;
	if (q_flag < 1)
	{
		v.value = get_env(node->name, v.start, v.end, &v);
		v.replace = replace_env(node->name, v.start - 1, &v, dq_flag);
		free(node->name);
		node->name = v.replace;
		v.len = ft_strlen(v.value);
		if (!v.value)
			return (v.start - 1);
		if (v.flag)
			free(v.value);
		return (v.start + v.len - 1);
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
			i = when_name_env(node, i, q_flag, dq_flag);
		else if (node->name[i] == '\'')
			when_name_q(node, &i, &q_flag, &dq_flag);
		else if (node->name[i] == '\"')
			when_name_dq(node, &i, &q_flag, &dq_flag);
		else
			i++;
	}
}
