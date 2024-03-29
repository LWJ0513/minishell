/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:32:35 by him               #+#    #+#             */
/*   Updated: 2023/04/10 20:13:51 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_doc(int *fd, char *with)
{
	char	*buff;
	int		len;

	len = 0;
	close(fd[0]);
	while (1)
	{
		buff = readline("heredoc> ");
		if (buff == 0)
			exit(0);
		if (ft_strcmp(buff, with) == 0)
		{
			write(fd[1], "\0", 1);
			break ;
		}
		len += ft_strlen(buff);
		if (len > 65534)
		{
			ft_putstr_fd("heredoc> Too many characters in the document.", 2);
			doc_util(0, buff, fd[1]);
		}
		print_buff(buff, fd[1]);
	}
	doc_util(1, buff, fd[1]);
}

int	stop_here_doc(int fd, t_rdir *rdir)
{
	rdir->here_doc_fd = 0;
	close(fd);
	write(2, "\n", 1);
	g_info.last_exit_num = 1;
	return (1);
}

int	make_here_doc(t_rdir *rdir)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1 || !rdir->with)
		ft_error_exit("pipe error", 1);
	ignore_signal();
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork error", 1);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint_handler);
		read_doc(fd, rdir->with);
	}
	close(fd[1]);
	wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
	if (status == 1)
		return (stop_here_doc(fd[0], rdir));
	rdir->here_doc_fd = fd[0];
	return (0);
}

int	ft_heredoc(t_cmd *cmd, int *flag)
{
	t_rdir	*tmp;

	tmp = cmd->rdir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			*flag = make_here_doc(tmp);
		if (*flag)
			return (*flag);
		tmp = tmp->next;
	}
	return (*flag);
}

int	check_heredoc(t_cmd *cmd)
{
	int	flag;

	flag = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		if (cmd->is_heredoc)
			flag = ft_heredoc(cmd, &flag);
		if (flag)
			return (flag);
		cmd = cmd->next;
	}
	return (flag);
}
