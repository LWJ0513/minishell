/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:16:44 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/11 05:48:35 by wonlim           ###   ########.fr       */
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

int	when_content_env(t_cmd *node, int i, int j, int q_flag)
{
	char	*replace;
	char	*value;
	int		start;
	int		end;

	i++;
	start = i;
	while (node->content[j][i] != '\'' && node->content[j][i] != '\"' \
	&& node->content[j][i] != ' ' && node->content[j][i] != '\0')
		i++;
	end = i;
	if (q_flag < 1)
	{
		value = get_env(node->content[j], start, end);
		replace = replace_env(node->content[j], start - 1, end, value);
		free(node->content[j]);
		if (!replace)
			set_content(node);
		else
			node->content[j] = replace;
		if (value)
			return (start + ft_strlen(value) - 1);
		return (start - 1);
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

void	replace_content(t_cmd *node)
{
	t_content_flag	flag;
	int				i;
	int				j;

	ft_bzero(&flag, sizeof(t_content_flag));
	j = 0;
	while (node->content && node->content[j])
	{
		i = 0;
		while (node->content && node->content[j] && node->content[j][i])
		{
			if (node->content[j][i] == '$' && node->content[j][i + 1])
				i = when_content_env(node, i, j, flag.q_flag);
			else if (node->content[j][i] == '\'')
				when_content_q(node, &i, j, &flag);
			else if (node->content[j][i] == '\"')
				when_content_dq(node, &i, j, &flag);
			else
				i++;
		}
		j++;
	}
}
