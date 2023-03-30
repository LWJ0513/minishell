/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:30:38 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/30 16:01:11 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*join_three(char *start, char *end, char *middle)
{
	char	*join_two;
	char	*ret;

	join_two = ft_strjoin(start, middle);
	ret = ft_strjoin(join_two, end);
	free(join_two);
	return (ret);
}

size_t	get_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs != NULL)
	{
		envs = envs->next;
		size++;
	}
	return (size);
}

char	**lst_to_arr(t_env *envs)
{
	char		**arr;
	size_t		size;
	size_t		i;

	size = get_size(envs);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		ft_error_exit("malloc error", 1);
	arr[size] = 0;
	i = 0;
	while (i < size && envs != NULL)
	{
		arr[i] = join_three(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}
	return (arr);
}
