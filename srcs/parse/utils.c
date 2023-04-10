/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:04:59 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 20:26:24 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*eliminate(char *str, char c)
{
	char	*result;
	int		i;

	result = malloc(ft_strlen(str) - count_char(str, c) + 1);
	if (!result)
		ft_error_exit("malloc error", 1);
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			result[i] = *str;
			i++;
		}
		str++;
	}
	result[i] = 0;
	return (result);
}

char	*cut_front(char *str)
{
	while (*str == ' ' || *str == '|')
	{
		if (*str == '|')
		{
			printf("zsh: parse error near `|'\n");
			return (0);
		}
		str++;
	}
	return (str);
}
