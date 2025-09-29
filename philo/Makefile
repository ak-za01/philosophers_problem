NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -pthread

SRCS =  philo.c init.c sim.c utils.c  actions.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
