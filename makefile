NAME = philo
INCLUDE = philo.h
OBJ = philo.c\
	  routine.c\
	  ft_putstr_fd.c\
	  atoi.c\
	  get_time.c\
	  routine_eat.c\
	  timestamp.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = ${OBJ}
OBJS = ${SRCS:.c=.o}

%.o:%.c ${INCLUDE}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${SRCS}
	make ${OBJS}
	cc ${CFLAGS} ${OBJS} -o ${NAME} 

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean;
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re