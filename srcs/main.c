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
		i++;
	}
	return (count);
}

int main(void)
{
	char *str;
	char **split_pipe;
	// int last_result;
	t_list list;
	t_node *node;
	t_node *last_node;

	while (1)
	{
		reset_list(&list);
		str = readline("minishell $ ");

		if (str)
		{

			list.cnt_pipe = count_pipe(str);
			split_pipe = ft_split(str, '|');

			// todo spilt_pipe free

			int i = 0;
			while (split_pipe[i])
			{
				node = make_node(split_pipe[i]);
				if (list.head == 0) {
					list.head = node;
				}
				else {
					last_node = get_last_node(list.head);
					last_node->next = node;
				}
				i++;
			}
			list.cnt_cmd = i;

			printf("pipe 갯수 : %d\ncmd 갯수 : %d\n", list.cnt_pipe, list.cnt_cmd);

			// 맨 마지막에 파이프가 있으면 pipe >  출력

			// todo 연결 리스트 free (각각의 노드 안에 있는 node.cmd free)

			// if (!ft_strncmp(split[0], "pwd", ft_strlen(split[0])))
			// 	last_result = ft_pwd();
			// if (!ft_strncmp(split[0], "cd", ft_strlen(split[0])))
			// 	last_result = ft_cd(comb_split(split, 1));
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		// system("leaks minishell");
		add_history(str);
		free_split(split_pipe);
		free(str);
	}
}
