/* ************************************************************************** */
/*                                                             `               */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:40:19 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 14:47:54 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int count_pipe(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
	}
	return (count);
}

int main(void)
{
	char *str;
	char **split_pipe;
	char **split_cmd;
	int last_result;
	t_list list;

	while (1)
	{
		reset_list(&list);
		str = readline("minishell $ ");

		list.cnt_cmd = count_pipe(str);
		split_pipe = ft_split(str, '|');

		// spilt free

		// 맨 마지막에 파이프가 있으면 pipe >  출력

		if (str)
		{
			split = ft_split(str, ' ');

			if (!ft_strncmp(split[0], "pwd", ft_strlen(split[0])))
				last_result = ft_pwd();
			if (!ft_strncmp(split[0], "cd", ft_strlen(split[0])))
				last_result = ft_cd(comb_split(split, 1));
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		// system("leaks minishell");
		add_history(str);
		free_split(split);
		free(str);
	}
}
