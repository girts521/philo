NAME = philo 
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS = main.c utils.c init_philo.c mutex_utils.c

OBJS  :=  $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS)

re: fclean all

.PHONY: all clean fclean re
