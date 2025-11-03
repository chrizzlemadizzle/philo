NAME = philo
SRCS = main.c init.c philo_utils.c routines.c routines_utils.c mutex_utils.c time_utils.c checks.c
OBJS = $(SRCS:.c=.o)

CC = cc
CCFlags = -Wall -Wextra -Werror -I. -O0 -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFlags) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all
