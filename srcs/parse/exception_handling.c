/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:35:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:32:18 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_last_pipe(char *str)
{
	int	size;

	size = ft_strlen(str);
	while (size > 0)
	{
		if (str[size - 1] == '|')
			return (1);
		if (str[size - 1] == ' ')
			size--;
		else
			return (0);
	}
	return (0);
}

int	when_q(t_rdir *r, int i)
{
	char	c;

	c = r->with[i];
	i++;
	while (r->with[i] != c)
		i++;
	return (i);
}

int	check_redirection_error(t_cmd *node, t_rdir *r, int i)
{
	while (node)
	{
		r = node->rdir;
		while (r)
		{
			i = 0;
			while (r->with && r->with[i])
			{
				if (r->with[i] == '\"' || r->with[i] == '\'')
					i = when_q(r, i);
				if (r->with[i] == '>' || r->with[i] == '<')
				{
					syntax_error();
					return (1);
				}
				i++;
			}
			r = r->next;
		}
		node = node->next;
	}
	return (0);
}

int	pipe_handling(char *str, t_mini *mini)
{
	if (check_last_pipe(str) && mini->cnt_pipe == mini->cnt_cmd)
	{
		mini->pipe_flag++;
		free_cmd(mini->cmds, mini->cnt_cmd);
		mini->cmds = 0;
		free(mini->line2);
		mini->line2 = 0;
		return (1);
	}
	if (mini->cnt_pipe > mini->cnt_cmd)
	{
		syntax_error();
		return (2);
	}
	return (0);
}

int	exception_handling(char *str, t_mini *mini)
{
	t_rdir	*node;
	int		value;

	value = pipe_handling(str, mini);
	if (value)
		return (value);
	if (mini->cnt_cmd != mini->cnt_node)
	{
		syntax_error();
		return (2);
	}
	if (mini->cmds)
	{
		node = mini->cmds->rdir;
		while (node)
		{
			if (!ft_strcmp(node->with, ""))
			{
				syntax_error();
				return (2);
			}
			node = node->next;
		}
	}
	return (0);
}
