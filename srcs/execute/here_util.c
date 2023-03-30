/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:22:04 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:27:25 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	doc_util(int num, char *buff, int fd)
{
	if (num == 0)
	{
		free(buff);
		close(fd);
		exit(1);
	}
	else if (num == 1)
	{	
		free(buff);
		close(fd);
		exit(0);
	}
}
