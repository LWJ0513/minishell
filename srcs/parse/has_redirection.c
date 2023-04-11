/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:35:13 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:35:25 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_redirection(char *str)
{
	char	c;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '<' || str[i] == '>'))
			return (1);
		if (flag == 0 && (str[i] == '\"' || str[i] == '\''))
		{
			flag = 1;
			c = str[i];
		}
		else if (flag == 1 && str[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (0);
}
