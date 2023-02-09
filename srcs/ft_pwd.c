#include "../include/minishell.h"

void    ft_pwd()
{
    char * buf = getcwd(0,0);
    printf("%s\n",buf);
    free(buf);
}