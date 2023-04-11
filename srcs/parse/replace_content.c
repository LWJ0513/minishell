/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:16:44 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:39:57 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*delete(char *str, int index)
{
	char	*new;
	int		i;
	int		j;

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
	return (new);
}

int	when_content_env(t_cmd *node, int i, int j, t_content_flag *f)
{
	t_val	v;

	v.start = ++i;
	while (node->content[j][i] != '\'' && node->content[j][i] != '\"' \
	&& node->content[j][i] != ' ' && node->content[j][i] != '\0')
		i++;
	v.end = i;
	if (f->q_flag < 1)
	{
		v.value = get_env(node->content[j], v.start, v.end, &v);
		v.replace = replace_env(node->content[j], v.start - 1, &v, f->dq_flag);
		if (!v.replace && !ft_strcmp(node->content[0], "echo"))
			set_i_content(node, f, j);
		else if (!v.replace)
			set_content(node, f);
		else
			node->content[j] = v.replace;
		v.len = ft_strlen(v.value);
		if (!v.value)
			return (v.start - 1);
		if (v.flag)
			free(v.value);
		return (v.start + v.len - 1);
	}
	return (i);
}

void	when_content_q(t_cmd *node, int *i, int j, t_content_flag *flag)
{
	char	*replace;

	if (flag->q_flag == 0 && flag->dq_flag == 0)
	{
		flag->q_flag = 1;
		replace = delete(node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else if (flag->q_flag == 1 && flag->dq_flag == 0)
	{
		flag->q_flag = 0;
		replace = delete(node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else
		*i += 1;
}

void	when_content_dq(t_cmd *node, int *i, int j, t_content_flag *flag)
{
	char	*replace;

	if (flag->q_flag == 0 && flag->dq_flag == 0)
	{
		flag->dq_flag = 1;
		replace = delete(node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else if (flag->q_flag == 0 && flag->dq_flag == 1)
	{
		flag->dq_flag = 0;
		replace = delete(node->content[j], *i);
		free(node->content[j]);
		node->content[j] = replace;
	}
	else
		*i += 1;
}

void	replace_content(t_cmd *node, int i, int j)
{
	t_content_flag	flag;

	ft_bzero(&flag, sizeof(t_content_flag));
	j = 0;
	while (node->content && node->content[j])
	{
		i = 0;
		while (node->content && node->content[j] && node->content[j][i])
		{
			if (node->content[j][i] == '$' && node->content[j][i + 1])
				i = when_content_env(node, i, j, &flag);
			else if (node->content[j][i] == '\'')
				when_content_q(node, &i, j, &flag);
			else if (node->content[j][i] == '\"')
				when_content_dq(node, &i, j, &flag);
			else
				i++;
		}
		if (flag.reset_content)
		{
			flag.reset_content = 0;
			continue ;
		}
		j++;
	}
}
