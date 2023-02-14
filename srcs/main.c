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

int main(int argc, char **argv, char **envp)
{
	if (argc)
	;
	if (argv)
	;
	char *str;
	char **split_pipe;
	// int last_result;
	t_list list;
	t_node *node;
	t_node *last_node;

	// t_mini mini;

	t_envp *env;
	env = envp_init(envp);
	if (env)
	;

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
				if (list.head == 0)
				{
					list.head = node;
				}
				else
				{
					last_node = get_last_node(list.head);
					last_node->next = node;
				}
				i++;
			}
			list.cnt_cmd = count_cmd(&list, i);

			if (i != list.cnt_cmd || list.cnt_pipe + 1 != list.cnt_cmd)
			{
				add_history(str);
				printf("Syntax error !\n");
				// todo free
				continue;
			}

			// 맨 마지막에 파이프가 있으면 pipe >  출력

			// todo 연결 리스트 free (각각의 노드 안에 있는 node.cmd free)

			/***
			 * 명령어 횟수 만큼 fork 
			*/
			i = 0;
			while (i < list.cnt_cmd)
			{
				t_node *n = list.head;

				list.pid = fork();

				if (list.pid > 0)
				{
					i++;
				}
				else if (list.pid == 0)
				{
					// 자식
					int j = 0;
					while (j < i)
					{
						n = n->next;
						j++;
					}
					printf("\"%s\"\n", (n->cmd)[0]);
					break;

				}
				else
				{
					// 에러
					break;
				}
			}

			// if (!ft_strncmp(split[0], "pwd", ft_strlen(split[0])))
			// 	last_result = ft_pwd();
			// if (!ft_strncmp(split[0], "cd", ft_strlen(split[0])))
			// 	last_result = ft_cd(comb_split(split, 1));
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

printf("끝 \n");

		// system("leaks minishell");
		add_history(str);
		free_split(split_pipe);
		free(str);
	}
}
