/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:34:29 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/12 07:35:28 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	while_str(char *str, int i)
{
	char	c;

	while (str[i] && str[i + 1] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i + 1] == '\'' || str[i + 1] == '\"')
				continue ;
		}
		if (str[i + 1] == ' ')
			break ;
		i++;
	}
	if (!str[i])
		return (i);
	return (++i);
}

int	left_redirection(char *str, int i, int *index, int *end)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		*index = i;
		*end = while_str(str, i);
		return (HEREDOC);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	*end = while_str(str, i);
	return (R_RDIR);
}

int	right_redirection(char *str, int i, int *index, int *end)
{
	if (str[i] == '>' && str[i + 1] == '>')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		*index = i;
		*end = while_str(str, i);
		return (D_RDIR);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	*end = while_str(str, i);
	return (RDIR);
}

int	when_else(char *str, int *i)
{
	char	c;

	while (ft_isprint(str[*i]) && str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			c = str[*i];
			*i += 1;
			while (str[*i] != c)
				*i += 1;
			if (str[*i + 1] == '\'' || str[*i + 1] == '\"')
			{
				*i += 1;
				continue ;
			}
		}
		if (str[*i] == '>' || str[*i] == '<' || str[*i] == ' ')
			return (0);
		*i += 1;
	}
	return (0);
}

int	check_redirection(char *str, int *index, int *end)
{
	int		i;

	i = *index;
	while (str[i])
	{
		if (str[i] == '<')
			return (left_redirection(str, i, index, end));
		else if (str[i] == '>')
			return (right_redirection(str, i, index, end));
		else
		{
			when_else(str, &i);
			*end = i;
			return (-1);
		}
		i++;
	}
	return (-2);
}
