/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:59:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:38:48 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	has_heredoc(t_cmd *node)
{
	t_rdir	*rdir_node;

	while (node)
	{
		if (node->rdir)
		{
			rdir_node = node->rdir;
			while (rdir_node)
			{
				if (rdir_node->type == HEREDOC)
				{
					node->is_heredoc = 1;
					return ;
				}
				rdir_node = rdir_node->next;
			}
		}
		node = node->next;
	}
}

t_cmd	*make_cmd_node(char *s, t_cmd *node, char *str)
{
	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_error_exit("malloc error", 1);
	ft_bzero(node, sizeof(t_cmd));
	str = cut_back_front(s);
	if (has_redirection(str))
	{
		if (make_rdir_node(node, str))
		{
			free(str);
			return (0);
		}
	}
	else
	{
		node->content = ft_split2(str);
		replace_content(node, 0, 0);
		if (node->content)
			node->name = node->content[0];
		if (node->content)
			set_content(node, 0);
	}
	free(str);
	has_heredoc(node);
	return (node);
}

void	handling_node(t_mini *mini, t_cmd *node)
{
	t_cmd	*last_node;

	if (mini->cmds == 0)
		mini->cmds = node;
	else
	{
		last_node = get_last_cmd_node(mini->cmds);
		last_node->next = node;
	}
}

int	if_null(char **split_pipe)
{
	free_split(split_pipe);
	return (1);
}

int	set_cmd_node(t_mini *mini, char	**split_pipe, t_cmd	*node, int i)
{
	while (split_pipe[i])
	{
		if (!ft_strcmp(split_pipe[i], ""))
		{
			i++;
			continue ;
		}
		node = make_cmd_node(split_pipe[i], 0, 0);
		if (!node)
			return (if_null(split_pipe));
		if (!node->name && !node->rdir)
		{
			free(split_pipe[i]);
			split_pipe[i] = remake_str(node);
			free_cmd(node, 1);
			continue ;
		}
		handling_node(mini, node);
		mini->cnt_cmd++;
		i++;
	}
	mini->cnt_cmd = count_cmd(mini, i);
	free_split(split_pipe);
	mini->cnt_node = i;
	return (0);
}
