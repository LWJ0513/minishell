#include "../include/minishell.h"

int    ft_pwd()
{
    char *buf;
    
    buf = getcwd(0, 0);
    printf("%s\n", buf);
    free(buf);
    return (0);
}
