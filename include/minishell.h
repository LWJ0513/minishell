/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/05 14:32:32 by wonlim           ###   ########.fr       */
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
	RDIR,		// 0  >
	R_RDIR,		// 1  <
	D_RDIR,		// 2  >>
	HEREDOC		// 3  <<
}	t_rdir_type;

typedef struct s_rdir
{
	int				type;			// t_rdir_type 넣는 변수
	int				here_doc_fd;	// 무조건 0으로 
	char			*with;			// 파일 이름 또는 eof (리다이렉션 문자 다음에 오는 거)
	struct s_rdir	*next;
}	t_rdir;

typedef struct s_cmd
{
	char			*name;			// 명령어 ls
	char			**content;		// 명령어 빼고 옵션  -a -l null
	struct s_rdir	*rdir;			// 리다이렉션 정보 넣는 연결리스트
	int				is_heredoc;		// << 이거 있는지만 체크 . 있으면 1 없으면 0
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
	int pipe_flag;
	int cnt_pipe;
	int cnt_cmd;
	int cnt_node;
	char *line;
	char *line2;
	char *str;
}	t_mini;


// parse
void	init_envp(char **envp);
void	ft_error_exit(char *str, int error_no);
void	set_terminal(void);
void set_signal();
void	ft_readline(t_mini *mini);
void	init_mini(t_mini *mini);
char	*eliminate(char *str, char c);
char	*cut_front(char *str);
void	set_cmd_node(char **split_pipe, t_mini *mini);
int	has_redirection(char *str);
void	make_rdir_node(t_cmd *node, char *str, int i, int end);
int	check_redirection(char *str, int *index, int *end);
int	count_options(t_rdir *r, int *index);
int	count_cmd(t_mini *mini, int max);
int	exception_handling(char *str, t_mini *mini);
int	count_pipe(char *str);
void free_split(char **split);
void free_cmd(t_cmd *head, int cnt);
void	free_main(t_mini *mini);
void	history(t_mini *mini);
int	count_char(char *str, char c);
void ignore_signal(void);
int valid_quotation(char *str);
void replace_content(t_cmd *node, int quotation_flag, int double_quotation_flag);
char *get_env(char *str, int start, int end);
char *replace_env(char *str, int start, int end, char *node);
char *delete(char *str, int index);
void replace_name(t_cmd *node, int quotation_flag, int double_quotation_flag);

char **ft_split2(char *str);


void rl_replace_line(const char *text, int clear_undo);

//ft_strjoin2.c
char	**ft_strjoin2(char *str, char **arr);

// find_env_add.c
t_env	*find_env_add(char *key);

// ft_error_exit.c
void	ft_command_error(char *cmd);

// ft_builtin.c
void	single_builtin(t_cmd *cmd);
int		check_builtin(char *cmd_name);
int		is_builtin(t_cmd *cmd);

// find_env.c
t_env	*find_env(char *key);

// ft_strcmp.c
int		ft_strcmp(const char *str1, const char *str2);

// ft_execute.c
void	execute(t_cmd	*cmd);

// ft_rdir.c
int		ft_rdir(t_rdir *rdir);

// ft_exit.c
void	ft_exit(t_cmd	*cmd);

// ft_cd.c
void	ft_cd(t_cmd	*cmd);

// ft_echo.c
void	ft_echo(t_cmd	*cmd);

// ft_env.c
void	ft_env(t_cmd	*cmd);

// ft_pwd.c
void	ft_pwd(void);

// ft_export.c
void	ft_export(char **str);

// ft_unset.c
void	ft_unset(t_cmd *cmd);

// ft_fork.c
void	ft_fork(int pipe_cnt, t_cmd *cmd);

// ft_here_doc.c
int		check_heredoc(t_cmd *cmd);

// ft_exe.c
void	ft_exe(t_cmd *cmd, t_env *env);

// signal.c
void	heredoc_sigint_handler(int signo);

// here_util.c
void	doc_util(int num, char *buff, int fd);
char	**lst_to_arr(t_env *envs);


#endif