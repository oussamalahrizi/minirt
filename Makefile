CC = cc
CFLAGS = -Wall -Wextra 

SRCS = 	main.c \
		vectors_utils.c \
		Sphere.c \
		camera.c \
		light.c \
		ray.c \
		image.c\
		image_utils.c\
		Gtform.c \
		init.c \
		matrix.c \
		Plane.c \
		object.c
	
OBJS = ${SRCS:.c=.o}

NAME = minirt

all : ${NAME}

%.o : %.c
	@$(CC) ${CFLAGS} -fsanitize=address -g3 -I/usr/include -Imlx_linux -O3 -c $< -o $@

${NAME} : ${OBJS}
	@$(CC) $(OBJS) -fsanitize=address -g3 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	@rm -rf ${OBJS}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean fclean re all