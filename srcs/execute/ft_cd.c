/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:55:18 by him               #+#    #+#             */
/*   Updated: 2023/03/30 02:26:08 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	edit_pwd(char	*cwd)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;

	env_pwd = find_env_add("PWD");
	env_oldpwd = find_env_add("OLDPWD");
	if (env_oldpwd->value)
		free(env_oldpwd->value);
	env_oldpwd->value = env_pwd->value;
	if (cwd)
		env_pwd->value = ft_strdup(cwd);
	else
		env_pwd->value = ft_strdup("");
	if (!env_pwd->value)
		ft_error_exit("malloc error", 1);
}

void	ft_cd(t_cmd	*cmd)
{
	char	get_cwd[PATH_MAX];
	char	*path;

	if (!cmd)
		return ;
	if (!cmd->content || *cmd->content == 0)
	{
		ft_putstr_fd("plese check argument\n", 2);
		g_info.last_exit_num = 1;
		return ;
	}
	path = *cmd->content;
	if (chdir(path) || !getcwd(get_cwd, PATH_MAX))
	{
		ft_putstr_fd("fail diretory change\n", 2);
		g_info.last_exit_num = 1;
		return ;
	}
	edit_pwd(get_cwd);
	g_info.last_exit_num = 0;
}
