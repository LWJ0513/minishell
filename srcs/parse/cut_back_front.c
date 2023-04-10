/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_back_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:27:10 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/11 03:30:17 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*make_str(char *s, int size, int start)
{
	char	*str;
	int		i;

	str = malloc(size + 1);
	i = 0;
	while (i < size)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*cut_back_front(char *s)
{
	int		start;
	int		cnt;
	int		i;

	start = 0;
	if (!s)
		return (0);
	while (s[start] == ' ')
		start++;
	i = ft_strlen(s) - 1;
	cnt = 0;
	while (s[i] == ' ')
	{
		cnt++;
		i--;
	}
	return (make_str(s, ft_strlen(s) - cnt - start, start));
}
