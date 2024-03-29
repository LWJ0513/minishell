/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:03:27 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:27:03 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	name_check(char *str)
{
	if (!str || *str == 0)
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		g_info.last_exit_num = 1;
		return (0);
	}
	if (!str || (*str == '_' && !ft_isalpha(*str)))
		return (0);
	str++;
	while (*str)
	{
		if ((!ft_isalpha(*str) && !ft_isdigit(*str) && *str != '_'))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			g_info.last_exit_num = 1;
			return (0);
		}
		str++;
	}
	g_info.last_exit_num = 0;
	return (1);
}

char	**find_key_value(char	*key_value)
{
	char			**res;
	unsigned int	len;

	if (!ft_strchr(key_value, '='))
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			ft_error_exit("malloc error", 1);
		res[0] = ft_strdup(key_value);
		res[1] = 0;
		return (res);
	}
	res = malloc(sizeof(char *) * 3);
	if (!res)
		ft_error_exit("malloc error", 1);
	len = ft_strchr(key_value, '=') - key_value;
	res[0] = malloc(sizeof(char) * len + 1);
	if (!res[0])
		ft_error_exit("malloc error", 1);
	ft_strlcpy(res[0], key_value, len + 1);
	res[1] = ft_strdup(key_value + len + 1);
	res[2] = 0;
	return (res);
}

void	export_null_print(void)
{
	t_env	*env;

	env = g_info.env_lst;
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
	g_info.last_exit_num = 0;
}

void	free_env_arr(char	**str)
{
	unsigned int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	free(str);
}

void	ft_export(char **str)
{
	t_env	*temp;
	char	**env_arr;
	size_t	i;

	i = -1;
	if (!str)
	{
		export_null_print();
		return ;
	}
	while (str[++i])
	{
		env_arr = find_key_value(str[i]);
		if (name_check(env_arr[0]))
		{
			temp = find_env_add(env_arr[0]);
			if (env_arr[1] != 0)
			{
				free(temp->value);
				temp->value = ft_strdup(env_arr[1]);
			}
		}
		free_env_arr(env_arr);
	}
}
