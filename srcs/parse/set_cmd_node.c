/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:59:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 17:21:17 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *get_last_cmd_node(t_cmd *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void has_heredoc(t_cmd *node)
{
	t_rdir *rdir_node;

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
					return;
				}
				rdir_node = rdir_node->next;
			}
		}
		node = node->next;
	}
}

void set_content(t_cmd *node)
{
	char **before;
	char **after;
	int i;
	int j;

	if (!node->content[1])
	{
		free(node->content);
		node->content = NULL;
		return;
	}
	before = node->content;
	i = 0;
	while (before[i])
	{
		i++;
	}
	after = malloc(sizeof(char *) * i);
	i = 0;
	j = 1;
	while (before[j])
	{
		after[i] = before[j];
		i++;
		j++;
	}
	after[i] = before[j];
	free(before);
	node->content = after;
}

char *cut_back(char *s)
{
	char *str;
	int i;
	int cnt;

	if (!s)
		return 0;
	i = ft_strlen(s) - 1;
	cnt = 0;
	while (s[i] == ' ')
	{
		cnt++;
		i--;
	}
	str = malloc(ft_strlen(s) - cnt + 1);
	i = 0;
	while (i < (int)ft_strlen(s) -cnt ){
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return str;
}

t_cmd *make_cmd_node(char *s)
{
	t_cmd *node;
	char *str;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_error_exit("malloc error", 1);
	ft_bzero(node, sizeof(t_cmd));
	str = cut_back(s);
	
	if (has_redirection(str))
		make_rdir_node(node, str, 0, 0);
	else
	{
		node->content = ft_split2(str);
		replace_content(node, 0, 0);
		node->name = node->content[0];
	}
	free(str);
	set_content(node);
	has_heredoc(node);
	return (node);
}

void set_cmd_node(char **split_pipe, t_mini *mini)
{
	t_cmd *node;
	t_cmd *last_node;
	int i;

	i = 0;
	while (split_pipe[i])
	{
		node = make_cmd_node(split_pipe[i]);
		if (mini->cmds == 0)
		{
			mini->cmds = node;
		}
		else
		{
			last_node = get_last_cmd_node(mini->cmds);
			last_node->next = node;
		}
		i++;
	}
	mini->cnt_cmd = count_cmd(mini, i);
	free_split(split_pipe);
	mini->cnt_node = i;
}
