#include "../include/minishell.h"

int    ft_pwd()
{
    printf("%s\n",getcwd(0,0));
    // t_e_node *tmp;

    // tmp=envp->head;

    // while (*(tmp->next->key))
    // {
    //     // printf("tmp->key : %s\n",tmp->key);
    //     if (!ft_strcmp(tmp->key, "PWD"))
    //     {
    //         printf("%s\n",tmp->value);
    //         return (0);
    //     }
    //     tmp=tmp->next;
    // }
    return (0);
    // char *buf;
    
    // buf = getcwd(0, 0);
    // printf("%s\n", buf);
    // free(buf);
    // return (0);
}
