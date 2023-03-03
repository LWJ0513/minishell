/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/03 19:20:46 by wonlim           ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_redirection
{
	int				flag;
	char			*file;
	struct t_red	*next;
}	t_red;

typedef struct s_node
{
	struct s_node			*prev;
	struct s_redirection	*r_node;
	struct s_node			*next;
	char				*cmd;
	char			**option;
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
	t_envp *env;
	t_envp *env_exp;
	int pipe_flag;
	int cnt_node;
	char *str;
	char *line;
	char *line2;
	char **path;

}	t_mini;

int		ft_pwd();
int		ft_cd(char *str, t_envp *envp);
void	free_split(char **split);
char	*comb_split(char **split, int i);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(t_envp *envp);
t_node	*make_node(char *str);
void	init_list(t_list *list);
void	init_node(t_node *node);
t_node	*get_last_node(t_node *node);
t_envp	*envp_init(char **envp);
int		count_pipe(char *str);
int		count_cmd(t_list *list, int max);
void    ft_export(char *str, t_mini *mini);
void    ft_print_export(t_envp *list);
void 	Insert(t_envp* list, char **tmp2, char *key1, char *value1);
void    ft_sort_envp(t_envp *list);
char	*eliminate(char *str, char c);
void	print_pipe(int cnt);
char	*cut_front(char *str);
int		check_last_pipe(char *str);
void	free_list(t_list *list, int cnt);
void 	execute_command_2(t_list *list, t_mini *mini, char **envp1);
char	*get_path(t_envp *env);
int		cmp_builtin(char *cmd);
void	search_path(char **path, t_node *node);
void	valid_cmd(char **path, t_list *list);
int		exception_handling(char *str, t_list *list, t_mini *mini);
void	init_mini(t_mini *mini);
void	set_node(char **split_pipe, t_list *list, t_mini *mini);
void	ft_readline(t_mini *mini, t_list *list);
void	free_main(t_mini *mini, t_list *list);
void	history(t_mini *mini);
int		count_char(char *str, char c);

void 	ft_echo(t_node *tmp);
void	ft_unset(char *str, t_mini *mini);
void	ft_exit(t_node *tmp, t_list *list);

t_envp *envp_exp_init(char **envp);

void	re_out_append(char *file_path);
void	re_out(char *file_path);
void	re_in(char *file_path);
void	ft_error(char *message);



#endif