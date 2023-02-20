/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:28:06 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/20 19:28:24 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_last_pipe(char *str)
{
	int size = ft_strlen(str);

	while (size > 0)
	{
		if (str[size - 1] == '|')
			return 1;
		if (str[size - 1] == ' ')
			size--;
		else
			return 0;
	}
	return 0;
}
