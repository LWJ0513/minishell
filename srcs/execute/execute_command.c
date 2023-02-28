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

void    execute_builtin(t_list *list, t_node *tmp, t_mini *mini)
{
    char *cmd;

    if (list)
        ;

    cmd  = tmp->cmd[0];
    if (!ft_strcmp(cmd, "echo"))
        ft_echo(tmp->cmd[0], tmp->cmd[1]);
    else if (!ft_strcmp(cmd, "cd"))
        ft_cd(tmp->cmd[1],mini->env);
    else if (!ft_strcmp(cmd, "env"))
        ft_env(mini->env);
    else if (!ft_strcmp(cmd, "pwd"))
        ft_pwd();
    else if (!ft_strcmp(cmd, "export"))
        ft_export(tmp->cmd[1], mini);
    else if (!ft_strcmp(cmd, "exit"))
        ft_exit(tmp, list);
    else if (!ft_strcmp(cmd, "unset"))
        ft_unset(tmp->cmd[1], mini);
}

int     is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "echo"))
        return (1);
    else if (!ft_strcmp(cmd, "cd"))
        return (1);
    else if (!ft_strcmp(cmd, "env"))
        return (1);
    else if (!ft_strcmp(cmd, "pwd"))
        return (1);
    else if (!ft_strcmp(cmd, "export"))
        return (2);
    else if (!ft_strcmp(cmd, "exit"))
        return (2);
    else if (!ft_strcmp(cmd, "unset"))
        return (2);
    return (0);
}

void execute_command_2(t_list *list, t_mini *mini, char **envp1)
{
    if (!envp1)
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
        if (is_builtin(tmp->cmd[0]) == 2)
        {
            execute_builtin(list, tmp, mini);
            tmp = tmp->next;
            i++;
            continue;
        }
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
            if (is_builtin(tmp->cmd[0]))
            {
                execute_builtin(list, tmp, mini);
                exit(0);
            }
            else
            {
                execvp(tmp->cmd[0], tmp->cmd);
            }
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