/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/13 21:10:28 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/history.h"
# include "readline/readline.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	int				result;
	char			**cmd;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	pid_t	pid;
	int		cnt_pipe;
	int		cnt_cmd;
}	t_list;

typedef struct s_e_node
{
	char	*key;
	char	*value;
	struct s_envp *next;
	struct s_envp *prev;
}	t_e_node;

typedef struct s_envp
{
	struct s_e_node *head;
}	t_envp;
int		ft_pwd(void);
int		ft_cd(char *str);
void	free_split(char **split);
char	*comb_split(char **split, int i);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(char **envp);
t_node	*make_node(char *str);
void	reset_list(t_list *list);
void	reset_node(t_node *node);
t_node	*get_last_node(t_node *node);
t_envp	*envp_init(char **envp);


#endif