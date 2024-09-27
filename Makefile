NAME = philo

SRCS = 	philosophers.c \
		parser.c \
		libft/ft_isdigit.c \
        libft/ft_putchar_fd.c \
        libft/ft_putendl_fd.c \
        libft/ft_putnbr_fd.c \
        libft/ft_putstr_fd.c \
        libft/ft_split.c \
		libft/ft_strjoin.c \
		libft/ft_strlcpy.c \
        libft/ft_strdup.c \
        libft/ft_strlen.c \
        libft/ft_strncmp.c \
		libft/ft_memcpy.c \
		libft/ft_strlcat.c \
		libft/ft_memset.c \
		libft/ft_atoi.c\
		libft/ft_substr.c\
		libft/ft_strchr.c\
		libft/ft_itoa.c\
		libft/ft_strnstr.c\
		libft/ft_strtrim.c\
		libft/ft_isalnum.c\
		libft/ft_isalpha.c\
		utils.c\
		utils2.c\
		init.c\
		dinner.c\
		synchro_utils.c\
		write.c\
		monitor.c\





OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
