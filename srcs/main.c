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

int main(int argc, char **argv, char **envp)
{
	char *str;
	char *line;
	char **split_pipe;
	t_list list;
	t_node *node;
	t_node *last_node;
	t_envp *env;
	// t_mini mini;
	// int last_result;

	env = envp_init(envp);
	if (env)
	;

	if (argc != 1 || !argv)
		exit(0);

	while (1)
	{
		reset_list(&list);
		line = readline("minishell $ ");

		if (line)
		{
			// todo front 예외처리
			str = cut_front(line);
			if (!str)
				continue;

			// - pipe 기준으로 split
			list.cnt_pipe = count_pipe(str);
			split_pipe = ft_split(str, '|');

			// todo spilt_pipe free

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
			if (i != list.cnt_cmd || list.cnt_pipe + 1 != list.cnt_cmd)
			{
				add_history(line);
				printf("Syntax error !\n");
				// todo free
				continue;
			}
			execute_command(&list, node, *node->cmd, env);
		}
		else // str = NULL 이라면 (EOF, cntl + D)
			break;

		// system("leaks minishell");
		add_history(line);
		free_split(split_pipe);
		free(line);
		// printf("while문끝부분\n");
		// ft_pwd(env);
	}
}
