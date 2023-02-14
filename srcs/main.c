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
	char *str;
	char **split_pipe;
	t_list list;
	t_node *node;
	t_node *last_node;
	t_envp *env;
	// t_mini mini;
	// int last_result;

	env = envp_init(envp);

	if (argc != 1 || !argv)
		exit(0);

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


			i = 0;
			int status;
			while (i < list.cnt_cmd)
			{
				node = list.head;

				list.pid = fork();

				if (list.pid > 0)
				{
					waitpid(list.pid, &status, 0);
					i++;
				}
				else if (list.pid == 0)
				{
					// 자식
					int j = 0;
					while (j < i)
					{
						node = node->next;
						j++;
					}
					printf("\"%s\"\n", (node->cmd)[0]);
					
					// todo execute_command() 함수 구현
					execute_command(node, &env);
					
					exit(0);
				}
				else
				{
					// 에러
					perror("fork error : ");
					exit(0);
				}
			}

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
