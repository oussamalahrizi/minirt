CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	main.c \
		vector_utils.c \
		Sphere.c \
		camera.c
	
OBJS = ${SRCS:.c=.o}

NAME = minirt

all : ${NAME}

%.o : %.c
	@$(CC) ${CFLAGS} -Imlx -c $< -o $@

${NAME} : ${OBJS}
	@$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : clean fclean re all