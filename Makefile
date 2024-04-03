NAME	 = Philo
CFLAGS	 = -Wall -Wextra -Werror -g ##-fsanitize=thread -gdwarf-4 
SRCS	 = philosophers.c philosophers_utils.c free.c init.c ##test.c
OBJS	 = ${SRCS:.c=.o}

%.o: %.c 
	gcc $(CFLAGS) $< -c -o $@ 

$(NAME) : $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
