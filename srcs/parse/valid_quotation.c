/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:16:26 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/11 02:07:28 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotation_even(char *str, int mark)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == mark)
			count++;
		i++;
	}
	return (count);
}

int	is_mix(char *str, int q_flag, int dq_flag, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' && q_flag == 0 && dq_flag == 0)
			q_flag = 1;
		else if (str[i] == '\'' && q_flag == 0 && dq_flag == 1)
			q_flag = 2;
		else if (str[i] == '\'' && q_flag == 1 && dq_flag == 0)
			q_flag = 0;
		else if (str[i] == '\'' && q_flag == 2 && dq_flag == 1)
			q_flag = 0;
		else if (str[i] == '\'' && q_flag == 1 && dq_flag == 2)
			return (1);
		if (str[i] == '\"' && q_flag == 0 && dq_flag == 0)
			dq_flag = 1;
		else if (str[i] == '\"' && q_flag == 0 && dq_flag == 1)
			dq_flag = 0;
		else if (str[i] == '\"' && q_flag == 1 && dq_flag == 0)
			dq_flag = 2;
		else if (str[i] == '\"' && q_flag == 1 && dq_flag == 2)
			dq_flag = 0;
		else if (str[i] == '\"' && q_flag == 2 && dq_flag == 1)
			return (1);
		i++;
	}
	return (0);
}

int	is_space(char *str)
{
	char	*check;

	check = eliminate(str, ' ');
	if (!ft_strcmp(check, "\"\"") || !ft_strcmp(check, "\'\'"))
	{
		free(check);
		return (1);
	}
	free(check);
	return (0);
}

int	valid_quotation(char *str)
{
	int	quotation_cnt;
	int	double_quotation_cnt;

	quotation_cnt = check_quotation_even(str, '\'');
	double_quotation_cnt = check_quotation_even(str, '\"');
	if (quotation_cnt % 2 != 0 || double_quotation_cnt % 2 != 0 \
		|| is_mix(str, 0, 0, 0))
	{
		syntax_error();
		return (1);
	}
	return (0);
}
