CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	main.c \
		vectors_utils.c \
		Sphere.c \
		camera.c \
		light.c
	
OBJS = ${SRCS:.c=.o}

NAME = minirt

all : ${NAME}

%.o : %.c
	@$(CC) ${CFLAGS} -Imlx -c $< -o $@

${NAME} : ${OBJS}
	@$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	@rm -rf ${OBJS}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean fclean re all