/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:43 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:25:36 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	re_out(char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_error("open fail");
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_error("dup2 fail");
	}
	close(fd);
}

void	re_out_append(char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_error("open fail");
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_error("dup2 fail");
	}
	close(fd);
}

void	re_in(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		ft_error("open fail");
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error("dup2 fail");
	close(fd);
}