/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:16:26 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/03 18:08:03 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_quotation_even(char *str, int mark)
{
	int count;
	int i;

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

int is_mix(char *str)
{
	int quotation_flag;
	int double_quotation_flag;
	int i;

	i = 0;
	quotation_flag = 0;
	double_quotation_flag = 0;
	/***
	 * 1 : outside
	 * 2 : inside
	 */

	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (quotation_flag == 0 && double_quotation_flag == 0)
				quotation_flag = 1;
			else if (quotation_flag == 0 && double_quotation_flag == 1)
				quotation_flag = 2;
			else if (quotation_flag == 1 && double_quotation_flag == 0)
				quotation_flag = 0;
			else if (quotation_flag == 2 && double_quotation_flag == 1)
				quotation_flag = 0;
			else if (quotation_flag == 1 && double_quotation_flag == 2)
				return 1;
		}

		if (str[i] == '\"')
		{
			if (quotation_flag == 0 && double_quotation_flag == 0)
				double_quotation_flag = 1;
			else if (quotation_flag == 0 && double_quotation_flag == 1)
				double_quotation_flag = 0;
			else if (quotation_flag == 1 && double_quotation_flag == 0)
				double_quotation_flag = 2;
			else if (quotation_flag == 1 && double_quotation_flag == 2)
				double_quotation_flag = 0;
			else if (quotation_flag == 2 && double_quotation_flag == 1)
				return 1;
		}

		i++;
	}
	return (0);
}

int is_space(char *str)
{
	char *check;

	check = eliminate(str, ' ');
	if (!ft_strcmp(check, "\"\"") || !ft_strcmp(check, "\'\'"))
	{
		free(check);
		return 1;
	}
	free(check);
	return 0;
}

int valid_quotation(char *str, t_mini *mini)
{
	int quotation_cnt;
	int double_quotation_cnt;

	// todo 따옴표, 쌍따옴표가 있는지 검사한다.

	// if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
	// 	return 0;

	// todo 있을 경우 짝수인지 검사한다.
	quotation_cnt = check_quotation_even(str, '\'');
	double_quotation_cnt = check_quotation_even(str, '\"');

	// todo 짝수가 아닐 경우 신택스 에러를 뱉는다.
	if (quotation_cnt % 2 != 0 || double_quotation_cnt % 2 != 0 || is_mix(str))
	{
		ft_printf("%s", "syntax error!\n");
		return (1);
	}
	if (is_space(str))
	{
		ft_printf("%s", ": command not found\n");
	}
	replace(mini, 0, 0);

	return 0;
}
