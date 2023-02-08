CC = cc
CFLAGS = -Wall -Werror -Wextra
OPTION = 
NAME = minishell
RM = rm -rf

MANDATORY = $(addprefix srcs/, $(SRCS))

SRCS =  \
	main.c 

OBJS = $(MANDATORY:c=o)

%.o : %c
	$(CC) $(OPTION) $(CFLAGS) -c -o $@ $^

$(NAME) : $(OBJS)
	$(CC) $(OPTION) $(CFLAGS) -o $@ $^ 

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re 