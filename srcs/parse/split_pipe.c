/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:16:36 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 19:50:51 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int cnt_cmd(char *str, int count, int flag, char c)
{
	if (ft_strlen(str) > 0)
		count++;
	while (*str == ' ')
		str++;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && !flag)
		{
			flag = 1;
			c = *str;
		}
		else if ((*str == '\'' || *str == '\"') && flag && c == *str)
			flag = 0;
		else if (*str == '|' && !flag)
		{
			count++;
			str++;
			while (*str == ' ')
				str++;
			continue;
		}
		str++;
	}
	return (count);
}

int count_pipe_len(char *str, int flag)
{
	int count;
	char c;

	count = 0;
	while (str[count])
	{
		if (str[count] == '\'' || str[count] == '\"')
		{
			if (!flag)
			{
				flag = 1;
				c = str[count];
			}
			else if (flag && c == str[count])
				flag = 0;
		}
		else if (str[count] == '|' && !flag)
			break;
		count++;
	}
	return (count);
}

void init_cmd(char **words, char *str, int count, int i)
{
	int j;

	while (*str == ' ')
		str++;
	while (*str)
	{
		count = count_pipe_len(str, 0);
		words[i] = malloc(count + 1);
		if (!words[i])
			ft_error_exit("malloc error", 1);
		j = 0;
		while (j < count)
		{
			words[i][j] = *str;
			str++;
			j++;
		}
		words[i][j] = '\0';
		i++;
		if (!*str)
			break;
		str++;
	}
	words[i] = 0;
}

char **ft_split_pipe(char *s)
{
	char **words;
	int count;

	if (!s)
		return (0);
	count = cnt_cmd(s, 0, 0, 0);

	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
	ft_error_exit("malloc error", 1);
	
	init_cmd(words, s, 0, 0);

	return words;
}