NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra  -Ofast -g3
LDFLAGS = -L./parse/libft -lft -lmlx -lXext -lX11 -lm -lz

LIBFT = parse/libft/libft.a

SRCS =	parse/tools.c 				\
		parse/tools2.c 				\
		parse/tools3.c 				\
		parse/parse.c 				\
		parse/whitesplit.c 			\
		parse/camera.c 				\
		parse/light.c 				\
		parse/ambient_lightning.c 	\
		parse/get_type.c				\
		parse/cylender.c 				\
		parse/sphere.c				\
		parse/plane.c

SRCS +=	camera.c \
		vectors.c \
		vectors2.c \
		vectors3.c \
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
		Objects/Sphere.c \
		Objects/Plane.c \
		Objects/Cylinder.c \
		Objects/Cylinder_utils.c \
		Materials/Diffuse.c \
		free_utils.c \
		random.c\
		init_objects.c


OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) ${LIBFT}
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

${LIBFT}:
	@make -C parse/libft >/dev/null

clean :
	@rm -rf $(OBJS)
	@make clean -C parse/libft >/dev/null

fclean : clean
	@rm -rf $(NAME) parse/libft/libft.a

re : fclean all

.PHONY : clean fclean all re