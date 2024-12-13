NAME = Philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): philo.c philo_utils.c init.c thread.c death_check.c subroutine.c
	@$(CC) $(CFLAGS)  -g3 $^ -o $@

clean:
	@rm -f  $(NAME)

fclean: clean

re: fclean all