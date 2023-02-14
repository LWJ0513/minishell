#include "../include/minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;
// 	int	size;

// 	size = 0;
// 	while (s1[size])
// 		size++;
// 	++size;
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (s1[i] == s2[i])
// 		{
// 			if (s1[i] == '\0')
// 				return (0);
// 			i++;
// 		}
// 		else
// 			return (s1[i] - s2[i]);
// 	}
// 	return (0);
// }

void    ft_sort_envp(t_envp *list)
{
    char *tmp;
    char **tmp1;
    t_e_node *index;

    tmp = NULL;
    tmp1 = NULL;
    index = list->head;
    while (index->next)
    {
        if (ft_strcmp(index->key, index->next->key) > 0)
        {
            tmp = index->key;
            index->key = index->next->key;
            index->next->key=tmp;
            tmp = index->value;
            index->value = index->next->value;
            index->next->value=tmp;
            tmp1 = index->split1;
            index->split1 = index->next->split1;
            index->next->split1=tmp1;
            index = list->head;
        }
        else
            index = index->next;
    }
}

void    ft_export(t_envp *list)
{
    t_e_node *tmp;

    tmp = list->head;
    while(tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void Insert(t_envp* list, char **tmp2, char *key1, char *value1) {
    t_e_node* newnode = (t_e_node*)malloc(sizeof(t_e_node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->split1=tmp2;
    newnode->key = key1;
    newnode->value = value1;
    t_e_node* tmp = list->head;
    if (tmp == NULL)
        list->head = newnode;
    else {
        newnode->next = tmp;
        tmp->prev = newnode;
        list->head = newnode;
    }
}

t_envp	*envp_init(char **envp)
{
    t_envp *new_env;
    char    **tmp;
    size_t     i;

    i = 0;
    new_env = (t_envp*)malloc(sizeof(t_envp));
    new_env->head=NULL;
    if (!new_env)
        printf("error");
    while (*(envp + i))
    {
        tmp = ft_split(*(envp + i), '=');
        Insert(new_env, tmp, tmp[0], tmp[1]);
        i++;
    }
    // t_e_node *tmp1 = new_env -> head; 

    // tmp1 = new_env -> head; 
    // while(tmp1)
    // {
    //     free(tmp1->split1);
    //     tmp1 = tmp1->next;
    // } 메모리누수처리
    ft_sort_envp(new_env);

    return (new_env);
}