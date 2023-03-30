CC = cc
CFLAGS = -Wall -Werror -Wextra -g
OPTION = -lreadline -L/opt/homebrew/opt/readline/lib
OPTION2 = -I/opt/homebrew/opt/readline/include/readline
# OPTION = -L$(shell brew --prefix readline)/lib
# OPTION2 = -I$(shell brew --prefix readline)/include
NAME = minishell
RM = rm -rf

MANDATORY_EXE = $(addprefix srcs/execute/, $(SRCS_EXE))
MANDATORY_PAR = $(addprefix srcs/parse/, $(SRCS_PAR))

SRCS_EXE =  \
	builtin.c \
    execute.c \
    ft_cd.c \
    ft_echo.c \
    ft_env.c \
    ft_exe.c \
    ft_exit.c \
    ft_export.c \
    ft_fork.c \
    ft_here_doc.c \
    ft_unset.c \
    ft_rdir.c \
    ft_pwd.c \
	here_util.c \
	execute_utils.c \
	find_env.c \
	find_env_add.c \
	ft_strcmp.c \
	ft_strjoin2.c
	
SRCS_PAR = \
	count.c \
	envp.c \
	exception_handling.c \
	exit_error.c \
	free.c \
	history.c \
	init.c \
	main.c \
	readline.c \
	redirection.c \
	set_cmd_node.c \
	set_rdir_node.c \
	signal.c \
	terminal.c \
	utils.c

OBJS = $(MANDATORY_EXE:c=o) $(MANDATORY_PAR:c=o)

%.o : %c
	$(CC) $(OPTION) $(OPTION2) $(CFLAGS) -c -o $@ $^

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft/
	$(CC) $(OPTION) $(OPTION2) $(CFLAGS) -o $@ $^ ./libft/libft.a 

all : $(NAME)
	

clean :
	$(MAKE) -C ./libft/ clean
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C ./libft/ fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re 