/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:15:33 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 00:08:12 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_words(char *str, int count, int flag, char c)
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
		else if (*str == ' ' && !flag)
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

int count_len(char *str, int *space, int flag)
{
	int count;
	char c;
	int space_i;

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
		else if (str[count] == ' ' && !flag)
		{
			*space = 0;
			space_i = count;
			while (str[space_i] == ' ')
			{
				*space += 1;
				space_i++;
			}
			break;
		}
		count++;
	}
	return (count);
}

void init_words2(char **words, char *str, int count, int i)
{
	int j;
	int space;

	while (*str == ' ')
		str++;
	while (*str)
	{
		count = count_len(str, &space, 0);
		if (!str[count])
			space = 0;
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
		str += space;
	}
	words[i] = 0;
}
// todo 문장의 뒤 고ㅇ백은 밖에서 자고 들ㅓㅗㄴ다고 가정

char **ft_split2(char *s)
{
	char **words;
	int count;

	if (!s)
		return (0);
	count = count_words(s, 0, 0, 0);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		ft_error_exit("malloc error", 1);
	init_words2(words, s, 0, 0);

	return (words);
}