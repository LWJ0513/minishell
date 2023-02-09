#include "../include/minishell.h"

void    ft_cd(char *str)
{
    int ret;

    ret = chdir(str);
    if (ret)
        perror("cd");
    else
    {
        chdir(str);
    }
}