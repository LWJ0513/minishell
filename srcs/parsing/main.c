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

#include "../../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *str;
	char *line;
	char *line2;
	char **split_pipe;
	t_list list;
	t_node *node;
	t_node *last_node;
	t_envp *env;
	t_mini mini;
	// int last_result;

	env = envp_init(envp);

	// todo env free

	if (argc != 1 || !argv)
		exit(0);

	mini.pipe_flag = 0;
	reset_list(&list);

	while (1)
	{

		if (!mini.pipe_flag)
			line = readline("minishell $ "); // malloc
		else
		{
			print_pipe(list.cnt_cmd);
			line2 = readline("> ");

			str = ft_strjoin(line, "\n");

			free(line);
			line = ft_strjoin(str, line2); // malloc
			free(line2);
			free(str);
			line2 = 0;
			str = 0;
		}

		if (line)
		{
			line2 = eliminate(line, '\n'); // malloc
			if (!line2){
				free(line);
				exit(0);
			}
			// - 앞 부분 예외처리
			str = cut_front(line2);
			if (!str || str[0] == '\0')
			{
				free(line);
				free(line2);
				continue;
			}

			// - pipe 기준으로 split
			list.cnt_pipe = count_pipe(str);
			split_pipe = ft_split(str, '|');

			// - command 를 노드화
			int i = 0;
			while (split_pipe[i])
			{
				node = make_node(split_pipe[i]); // malloc node~
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
			free_split(split_pipe);

			// - 예외처리
			if (check_last_pipe(str) && list.cnt_pipe == list.cnt_cmd)
			{
				mini.pipe_flag++;
				free_list(&list, list.cnt_cmd);
				list.head = 0;
				free(line2);
				continue;
			}
			if (i != list.cnt_cmd || list.cnt_pipe + 1 != list.cnt_cmd)
			{
				add_history(line2);
				printf("Syntax error !\n");
				free(line);
				free(line2);
				free_list(&list, list.cnt_cmd);
				continue;
			}

			execute_command_2(&list, node, *node->cmd, env, envp);
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		if (!mini.pipe_flag)
			add_history(line);
		else
			add_history(line2);
		free(line);
		free(line2);

		free_list(&list, list.cnt_cmd);

		// - 변수 초기화
		mini.pipe_flag = 0;
		reset_list(&list);

		// system("leaks --list -- minishell");
	}
}
