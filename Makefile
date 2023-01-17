NAME= philo.a

CC = gcc
CFLAGS= -Wall -Werror -Wextra -pthread -g
# -fsanitize=thread
HEADER= philo.h
RM= rm -rf
NAME = philo
#DEBUG = -fsanitize=address

LIBFT= include/libft/libft.a

FILES=	files/main.c \
		files/handle_input.c \
		files/routine.c \
		files/utils.c

# testing/threading.c
O_FILES= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(O_FILES)
	$(MAKE) -C include/libft
	$(CC) $(CFLAGS) $(DEBUG) $(O_FILES) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C include/libft
	$(RM) $(O_FILES)
	
fclean: clean
	$(MAKE) fclean -C include/libft
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re