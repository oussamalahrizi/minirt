CC = cc
CFLAGS = -Wall -Wextra

SRCS = 	main.c \
		vectors_utils.c \
		Sphere.c \
		camera.c \
		light.c \
		ray.c
	
OBJS = ${SRCS:.c=.o}

NAME = minirt

all : ${NAME}

%.o : %.c
	@$(CC) ${CFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

${NAME} : ${OBJS}
	@$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	@rm -rf ${OBJS}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean fclean re all