/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:34:29 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/14 15:50:41 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	left_redirection(char *str, int *index, int *end)
{
	int	i;

	i = *index;
	if (str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		*index = i;
		while (str[i + 1] != ' ' && str[i + 1] != '>' \
		&& str[i + 1] != '<' && str[i + 1] != '\0')
			i++;
		*end = ++i;
		return (4);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	while (str[i + 1] != ' ' && str[i + 1] != '>' \
	&& str[i + 1] != '<' && str[i + 1] != '\0')
		i++;
	*end = ++i;
	return (3);
}

int	right_redirection(char *str, int *index, int *end)
{
	int	i;

	i = *index;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		*index = i;
		while (str[i + 1] != ' ' && str[i + 1] != '>' \
		&& str[i + 1] != '<' && str[i + 1] != '\0')
			i++;
		*end = ++i;
		return (2);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	while (str[i + 1] != ' ' && str[i + 1] != '>' \
	&& str[i + 1] != '<' && str[i + 1] != '\0')
		i++;
	*end = ++i;
	return (1);
}

int	check_redirection(char *str, int *i, int *end)
{
	int	result;

	if (str[*i] == '<')
		result = left_redirection(str, i, end);
	else if (str[*i] == '>')
		result = right_redirection(str, i, end);
	else
	{
		while (ft_isprint(str[*i]) && str[*i] != ' ' \
		&& str[*i] != '>' && str[*i] != '<' && str[*i + 1] != '\0')
			*i += 1;
		*end = *i;
		result = 0;
	}
	return (result);
}
