/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:16:44 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/03 18:07:46 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *delete(char *str, int index)
{
	char *new;
	int i;
	int j;

	new = malloc(ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != index)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';

	return new;
}

int when_env(t_mini *mini, int i, int quotation_flag)
{
	int start;
	int end;
	char *replace;
	char *value;

	i++;
	start = i;
	while (mini->str[i] != '\'' && mini->str[i] != '\"' && mini->str[i] != ' ' && mini->str[i] != '\0')
	{
		i++;
	}
	end = i;

	if (quotation_flag < 1)
	{
		value = get_env(mini->str, start, end);
		replace = replace_env(mini->str, start - 1, end, value);
		free(mini->str);
		mini->str = replace;
		if (value)
			return start + ft_strlen(value) -1;
		else
			return start -1;
	}

	return i ;
}

void when_quotation(t_mini *mini, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*quotation_flag = 1;
		replace = delete (mini->str, *i);
		free(mini->str);
		mini->str = replace;
	}
	else if (*quotation_flag == 1 && *double_quotation_flag == 0)
	{
		*quotation_flag = 0;
		replace = delete (mini->str, *i);
		free(mini->str);
		mini->str = replace;
	}
	else
		*i += 1;
}

void when_double_quotation(t_mini *mini, int *i, int *quotation_flag, int *double_quotation_flag)
{
	char *replace;

	if (*quotation_flag == 0 && *double_quotation_flag == 0)
	{
		*double_quotation_flag = 1;
		replace = delete (mini->str, *i);
		free(mini->str);
		mini->str = replace;
	}
	else if (*quotation_flag == 0 && *double_quotation_flag == 1)
	{
		*double_quotation_flag = 0;
		replace = delete(mini->str, *i);
		free(mini->str);
		mini->str = replace;
	}
	else
		*i += 1;
}

void replace(t_mini *mini, int quotation_flag, int double_quotation_flag)
{
	int i;

	i = 0;
	while (mini->str[i])
	{
		if (mini->str[i] == '$')
		{
			i = when_env(mini, i, quotation_flag) ;
		}
		else if (mini->str[i] == '\'')
		{
			when_quotation(mini, &i, &quotation_flag, &double_quotation_flag);
		}
		else if (mini->str[i] == '\"')
		{
			when_double_quotation(mini, &i, &quotation_flag, &double_quotation_flag);
		}
		else
			i++;
	}
}