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

int main(void)
{
	char *str;
	char **split;

	while (1)
	{

		str = readline("minishell: $ ");
		if (str)
		{
			// printf("%s\n", str);
			split = ft_split(str, ' ');
			// todo split 이차원 포인터 malloc
			if (!ft_strncmp(split[0], "pwd", ft_strlen(split[0])))
				ft_pwd();
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		add_history(str);
		free(str);
	}
	return (0);
}
