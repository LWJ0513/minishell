#include "../include/minishell.h"

void    ft_env(char **envp)
{
    char *arg[] = {"/usr/bin/env", (char *)0};
    execve("/usr/bin/env", arg, envp);
    exit(0);
}