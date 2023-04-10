/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:35:22 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/11 03:23:15 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exception(t_cmd *node)
{
	t_rdir	*r;

	r = node->rdir;
	while (r)
	{
		if (!r->with && r->type != -1)
		{
			syntax_error();
			free_cmd(node, 1);
			return (1);
		}
		r = r->next;
	}
	return (0);
}

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
	if (check_redirection_error(mini->cmds, 0, 0))
	{
		free_cmd(mini->cmds, mini->cnt_cmd);
		mini->cmds = 0;
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
