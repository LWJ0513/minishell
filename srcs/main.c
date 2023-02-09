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
			split = ft_split(str, ' ');

			if (!ft_strncmp(split[0], "pwd", ft_strlen(split[0])))
				ft_pwd();
			if (!ft_strncmp(split[0], "cd", ft_strlen(split[0])))
				ft_cd(comb_split(split, 1));
		}
		else		 // str = NULL 이라면 (EOF, cntl + D)
			break;

		// system("leaks minishell");
		add_history(str);
		free_split(split);
		free(str);
	}
}
