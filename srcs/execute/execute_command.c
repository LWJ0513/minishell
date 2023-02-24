/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:43 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/24 15:25:36 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_command_2(t_list *list, t_node *node, char *cmd, t_envp *envp, char **envp1)
{
    if (!node | !cmd | !envp | !envp1)
        ;
    pid_t pid;
    t_node *tmp;
    tmp =list->head;
    int i, status=0;
    i = 0;
    int pipes[list->cnt_pipe][2];
    while (i < list->cnt_pipe)
    {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    while (i < list->cnt_pipe + 1)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if(i < list->cnt_pipe){
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            if (i != 0){
                dup2(pipes[i-1][0], STDIN_FILENO);
            }

            for (int j = 0; j < list->cnt_pipe; j++){
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            execvp(tmp->cmd[0], tmp->cmd);
        }
        tmp = tmp->next;
        i++;
    }
    for(int j = 0; j < list->cnt_pipe; j++){
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
    waitpid(pid, &status, 0);
    
}