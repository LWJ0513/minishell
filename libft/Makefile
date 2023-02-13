CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = libft.a
HEADER = libft.h

SRCS = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_itoa.c \
	ft_split.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_div_hexa.c \
	ft_printf_itoa.c \
	ft_printf.c \
	ft_putchar.c \
	ft_putstr.c \
	get_next_line.c


OBJS = $(SRCS:.c=.o)

%o : %c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		ar rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)
re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re