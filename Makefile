NAME = minirt
CC = cc
CFLAGS = -Wall -Wextra  -Ofast -g3
LDFLAGS = -lmlx -lXext -lX11 -lm -lz

SRCS =	camera.c \
		vectors.c \
		Matrix/init.c \
		Matrix/inverse.c \
		Matrix/matrix.c \
		Matrix/Minor.c \
		Matrix/Multiplication.c \
		Transformation/Gtfm.c \
		Transformation/setup.c \
		image/image.c \
		image/image_utils.c \
		Normals.c \
		raytrace.c \
		main.c \
		init_objects.c \
		Objects/Sphere.c \
		Objects/Plane.c \
		Objects/Cylinder.c \
		Objects/Cylinder_utils.c \
		Materials/Diffuse.c \
		free_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean all re