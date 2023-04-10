/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:19:20 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>

# define PATH_MAX 4096

typedef enum e_rdir_type
{
	RDIR,
	R_RDIR,
	D_RDIR,
	HEREDOC
}	t_rdir_type;

typedef struct s_rdir
{
	int				type;
	int				here_doc_fd;
	char			*with;
	struct s_rdir	*next;
}	t_rdir;

typedef struct s_cmd
{
	char			*name;
	char			**content;
	struct s_rdir	*rdir;
	int				is_heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	struct s_env	*env_lst;
	int				last_exit_num;
}	t_info;

extern t_info	g_info;

typedef struct s_mini
{
	t_cmd	*cmds;
	char	*line;
	char	*line2;
	char	*str;
	int		pipe_flag;
	int		cnt_pipe;
	int		cnt_cmd;
	int		cnt_node;
}	t_mini;

void	init_envp(char **envp);
void	ft_error_exit(char *str, int error_no);
void	set_terminal(void);
void	set_signal(void);
int		ft_readline(t_mini *mini);
void	init_mini(t_mini *mini);
char	*eliminate(char *str, char c);
char	*cut_front(char *str);
int		set_cmd_node(t_mini *mini);
int		has_redirection(char *str);
int		make_rdir_node(t_cmd *node, char *str);
int		check_redirection(char *str, int *index, int *end);
int		count_options(t_rdir *r, int *index);
int		count_cmd(t_mini *mini, int max);
int		exception_handling(char *str, t_mini *mini);
int		count_pipe(char *str);
void	free_split(char **split);
void	free_cmd(t_cmd *head, int cnt);
void	free_main(t_mini *mini);
void	history(t_mini *mini);
int		count_char(char *str, char c);
void	ignore_signal(void);
int		valid_quotation(char *str);
void	replace_content(t_cmd *node, int q_flag, int dq_flag);
char	*get_env(char *str, int start, int end);
char	*replace_env(char *str, int start, int end, char *node);
char	*delete(char *str, int index);
void	replace_name(t_cmd *node, int q_flag, int dq_flag);
char	**ft_split2(char *str);
char	**ft_split_pipe(char *str);
void	replace_with(t_cmd *node, int q_flag, int dq_flag);
char	*cut_back_front(char *s);
void	rl_replace_line(const char *text, int clear_undo);
int		check_exception(t_cmd *node);
t_rdir	*get_last_rdir_node(t_rdir *node);
void	set_cmd_options(t_cmd *node, int index);

t_cmd	*get_last_cmd_node(t_cmd *node);
char	*remake_str(t_cmd *node);
char	**ft_strjoin2(char *str, char **arr);
t_env	*find_env_add(char *key);
void	ft_command_error(char *cmd);
void	single_builtin(t_cmd *cmd);
int		check_builtin(char *cmd_name);
int		is_builtin(t_cmd *cmd);
t_env	*find_env(char *key);
int		ft_strcmp(const char *str1, const char *str2);
void	execute(t_cmd	*cmd);
int		ft_rdir(t_rdir *rdir);
void	ft_exit(t_cmd	*cmd);
void	ft_cd(t_cmd	*cmd);
void	ft_echo(t_cmd	*cmd);
void	ft_env(t_cmd	*cmd);
void	ft_pwd(void);
void	ft_export(char **str);
void	ft_unset(t_cmd *cmd);
void	ft_fork(int pipe_cnt, t_cmd *cmd);
int		check_heredoc(t_cmd *cmd);
void	ft_exe(t_cmd *cmd, t_env *env);
void	heredoc_sigint_handler(int signo);
void	doc_util(int num, char *buff, int fd);
char	**lst_to_arr(t_env *envs);
void	print_buff(char *buff, int fd);

#endif