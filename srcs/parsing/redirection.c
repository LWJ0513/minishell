/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:34:29 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/09 23:20:35 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int has_redirection(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int check_redirection(char *str, int i, int *end)
{

	if (str[i] == '<' && str[i + 1] == '<')
	{
		i++;
		while (str[i] == ' ')
			i++;
		while (str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			i++;
		*end = ++i;
		return 4;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		i++;
		while (str[i] == ' ')
			i++;
		while (str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			i++;
		*end = ++i;
		return 2;
	}
	else if (str[i] == '<')
	{
		while (str[i] == ' ')
			i++;
		while (str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			i++;
		*end = ++i;
		return 3;
	}
	else if (str[i] == '>')
	{
		while (str[i] == ' ')
			i++;

		while (str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			i++;
		*end = ++i;
		return 1;
	}
	while (ft_isprint(str[i]) && str[i] != ' ' && str[i] != '>' && str[i] != '<')
	{
		i++;
	}
	*end = i;
	return 0;
}