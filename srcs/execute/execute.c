/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:54:05 by him               #+#    #+#             */
/*   Updated: 2023/04/10 20:01:14 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(t_cmd	*cmd)
{
	int	p_in;
	int	p_out;

	p_in = dup(STDIN_FILENO);
	p_out = dup(STDOUT_FILENO);
	if (check_builtin(cmd->name) && !cmd->next)
	{
		single_builtin(cmd);
	}
	else if (cmd && cmd->name)
		ft_fork(0, cmd);
	else if (!cmd || !cmd->name)
		ft_rdir(cmd->rdir);
	dup2(p_in, STDIN_FILENO);
	dup2(p_out, STDOUT_FILENO);
}

int	pipe_count(t_cmd	*cmd)
{
	int	count;

	count = -1;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

void	execute(t_cmd	*cmd)
{
	int		pipe_cnt;

	if (!cmd)
		return ;
	pipe_cnt = pipe_count(cmd);
	if (check_heredoc(cmd))
		return ;
	if (cmd->next == 0)
		single_command(cmd);
	else
		ft_fork(pipe_cnt, cmd);
	return ;
}
