/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/20 20:03:36 by wonlim           ###   ########.fr       */
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
	char    **split1;
	char	*key;
	char	*value;
	struct s_e_node *next;
	struct s_e_node *prev;
}	t_e_node;

typedef struct s_envp
{
	struct s_e_node *head;
}	t_envp;

typedef struct s_mini
{
	int pipe_flag;
}	t_mini;

int		ft_pwd();
int		ft_cd(char *str, t_envp *envp);
void	free_split(char **split);
char	*comb_split(char **split, int i);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(char **envp);
t_node	*make_node(char *str);
void	reset_list(t_list *list);
void	reset_node(t_node *node);
t_node	*get_last_node(t_node *node);
t_envp	*envp_init(char **envp);
int		count_pipe(char *str);
int		count_cmd(t_list *list, int max);
void 	execute_command(t_list *list, t_node *node, char *cmd,t_envp *envp);
void 	execute_command_not_builtin(t_list *list, t_node *node, t_envp *envp, char *cmd);
void    ft_export(char *str, t_envp *envp);
void    ft_print_export(t_envp *list);
void 	Insert(t_envp* list, char **tmp2, char *key1, char *value1);
void    ft_sort_envp(t_envp *list);
char	*eliminate(char *str, char c);
void	print_pipe(int cnt);
char	*cut_front(char *str);
int		check_last_pipe(char *str);
void	free_list(t_list *list, int cnt);
void 	execute_command_2(t_list *list, t_node *node, char *cmd, t_envp *envp, char **envp1);

#endif