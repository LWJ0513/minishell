/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:55:28 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:26:00 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		ft_export(cmd->content);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd);
	return (0);
}

void	single_builtin(t_cmd *cmd)
{
	if (ft_rdir(cmd->rdir))
		return ;
	is_builtin(cmd);
}

int	check_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}
