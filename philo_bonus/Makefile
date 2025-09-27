NAME = philo_bonus

CC = cc

# FLAGS = -Wall -Wextra -Werror -pthread
FLAGS = -pthread

SRCS =  philo_bonus.c init_bonus.c sim_bonus.c utils_bonus.c\
		actions_bonus.c sim_utils_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
