/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:12:43 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 20:27:33 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_buff(char *buff, int fd)
{
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
}
