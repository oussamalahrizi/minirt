NAME = minirt
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
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
		parse/plane.c \
		parse/cone.c

SRCS +=	camera.c \
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
		Objects/Cone.c \
		Objects/Cone_utils.c \
		Materials/Diffuse.c \
		Materials/Specular.c \
		Materials/Simple_material.c \
		Materials/Reflection.c \
		textures/checker.c \
		textures/bump_map.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

${LIBFT}:
	@make -C parse/libft >/dev/null

clean :
	@rm -rf $(OBJS)
	@make clean -C parse/libft >/dev/null

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAME) parse/libft/libft.a

re : fclean all

.PHONY : clean fclean all re
