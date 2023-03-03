CC = cc
CFLAGS = -Wall -Werror -Wextra -g
OPTION = -lreadline -L/opt/homebrew/opt/readline/lib
OPTION2 = -I/opt/homebrew/opt/readline/include
NAME = minishell
RM = rm -rf

MANDATORY_EXE = $(addprefix srcs/execute/, $(SRCS_EXE))
MANDATORY_PAR = $(addprefix srcs/parsing/, $(SRCS_PAR))

SRCS_EXE =  \
	ft_pwd.c \
	ft_cd.c \
	ft_strcmp.c \
	ft_env.c \
	ft_generate_env.c \
	execute_command.c \
	ft_export.c\
	ft_echo.c\
	ft_exit.c\
	ft_unset.c\
	here_doc.c\
	ft_re.c\
	ft_error.c
	
SRCS_PAR = \
	main.c \
	free.c \
	comb_split.c \
	utils.c \
	count.c \
	valid_cmd.c \
	exception_handling.c \
	init.c \
	readline.c \
	set_node.c \
	history.c

OBJS = $(MANDATORY_EXE:c=o) $(MANDATORY_PAR:c=o)

%.o : %c
	$(CC) $(OPTION) $(CFLAGS) -c -o $@ $^

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