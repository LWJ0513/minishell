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

char *cut_front(char *str)
{

	while (*str == ' ' || *str == '|')
	{
		if (*str == '|')
		{
			printf("zsh: parse error near `|'\n");
			return 0;
		}
		str++;
	}
	return str;
}

int check_last_pipe(char *str)
{
	int size = ft_strlen(str);

	while (size > 0)
	{
		if (str[size - 1] == '|')
			return 1;
		if (str[size - 1] == ' ')
			size--;
		else
			return 0;
	}
	return 0;
}

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
	if (env)
		;
	// todo env free

	if (argc != 1 || !argv)
		exit(0);

	mini.pipe_flag = 0;
	reset_list(&list);

	while (1)
	{

		if (!mini.pipe_flag)
			line = readline("minishell $ ");
		else
		{
			while (list.cnt_cmd > 0)
			{
				printf("pipe ");
				list.cnt_cmd--;		// 얘를 깎아? 이 부분 함수 다시 짜기
			}
			line2 = readline("> ");

			str = ft_strjoin(line, "\n");
			free(line);
			line = ft_strjoin(str, line2);
			free(line2);
			free(str);
			line2 = line;
		}

		if (line || line2)
		{
			line = eliminate(line, '\n');
			// - 앞 부분 예외처리
			str = cut_front(line);
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

			// - 예외처리
			if (check_last_pipe(str) && list.cnt_pipe == list.cnt_cmd)
			{
				mini.pipe_flag++;
				// todo 연결리스트 free
				list.head = 0;
				continue;
			}
			if (i != list.cnt_cmd || list.cnt_pipe + 1 != list.cnt_cmd)
			{

				add_history(line2);
				printf("Syntax error !\n");
				// todo free
				continue;
			}

			execute_command(&list, node, *node->cmd, env);
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		// system("leaks minishell");
		if (mini.pipe_flag)
		{
			add_history(line2);
			free(line2);
		}
		else
		{
			add_history(line);
			free(line);
		}
		free_split(split_pipe);

		// - 변수 초기화
		mini.pipe_flag = 0;
		reset_list(&list);
		// todo node 연결리스트 free
	}
	// todo 중간에서 탈출할 때 free 확인하기 + line free
}
