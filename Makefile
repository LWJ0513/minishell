CC = cc
CFLAGS = -Wall -Werror -Wextra
OPTION = -lreadline -L/opt/homebrew/opt/readline/lib
OPTION2 = -I/opt/homebrew/opt/readline/include
NAME = minishell
RM = rm -rf

MANDATORY = $(addprefix srcs/, $(SRCS))

SRCS =  \
	main.c \


OBJS = $(MANDATORY:c=o)

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