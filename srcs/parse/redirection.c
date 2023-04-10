/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:34:29 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:51:10 by wonlim           ###   ########.fr       */
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

int	left_redirection(char *str, int i, int *index, int *end)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		*index = i;
		while (str[i] && str[i + 1] != ' ' && str[i + 1] != '>' \
		&& str[i + 1] != '<' && str[i + 1] != '\0')
			i++;
		*end = ++i;
		return (HEREDOC);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	while (str[i] && str[i + 1] != ' ' && str[i + 1] != '>' \
	&& str[i + 1] != '<' && str[i + 1] != '\0')
		i++;
	*end = ++i;
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
		while (str[i] && str[i + 1] != ' ' && str[i + 1] != '>' \
		&& str[i + 1] != '<' && str[i + 1] != '\0')
			i++;
		*end = ++i;
		return (D_RDIR);
	}
	i++;
	while (str[i] == ' ')
		i++;
	*index = i;
	while (str[i] && str[i + 1] != ' ' && str[i + 1] != '>' \
	&& str[i + 1] != '<' && str[i + 1] != '\0')
		i++;
	*end = ++i;
	return (RDIR);
}

int	when_else(char *str, int *i, int *flag, char *c)
{
	while (ft_isprint(str[*i]) && str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (!*flag)
			{
				*flag = 1;
				*c = str[*i];
			}
			else if (*flag && *c == str[*i])
				*flag = 0;
		}
		else if ((str[*i] == '>' || str[*i] == '<') && !*flag)
			return (1);
		*i += 1;
	}
	return (0);
}

int	check_redirection(char *str, int *index, int *end)
{
	char	c;
	int		flag;
	int		i;

	flag = 0;
	i = *index;
	while (str[i])
	{
		if (str[i] == '<')
			return (left_redirection(str, i, index, end));
		else if (str[i] == '>')
			return (right_redirection(str, i, index, end));
		else
		{
			if (when_else(str, &i, &flag, &c))
				break ;
			*end = i;
			return (-1);
		}
		i++;
	}
	return (-2);
}
