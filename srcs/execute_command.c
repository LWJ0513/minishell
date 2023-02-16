#include "../include/minishell.h"

void execute_command(t_list *list, t_node *node, char *cmd, t_envp *envp)
{
    if (cmd)
	    ;
    int i;
    i = 0;
    // int status;
    while (i < list->cnt_cmd)
    {
        node = list->head;

        int j = 0;
        while (j < i)
        {
            node = node->next;
            j++;
        }
        if (!ft_strcmp(cmd, "cd"))
        {
            ft_cd(node->cmd[1],envp);
        }
        else if (!ft_strcmp(cmd, "pwd"))
            ft_pwd(envp);
        else if (!ft_strcmp(cmd, "export"))
            ft_export(node->cmd[1],envp);
        i++;
    }
}

void execute_command_not_builtin(t_list *list, t_node *node, t_envp *envp, char *cmd)
{
    if (envp)
	    ;
    if (cmd)
	    ;
    int i;
    i = 0;
    int status;
    while (i < list->cnt_cmd)
    {
        node = list->head;

        list->pid = fork();

        if (list->pid > 0)
        {
            waitpid(list->pid, &status, 0);
            i++;
        }
        else if (list->pid == 0)
        {
            // 자식
            int j = 0;
            while (j < i)
            {
                node = node->next;
                j++;
            }
            exit(0);
        }
        else
        {
            // 에러
            perror("fork error : ");
            exit(0);
        }
    }
}