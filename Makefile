




NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -g3 -fsanitize=address
LDFLAGS = -L./libft -lft -lmlx -lXext -lX11 -lm -lz

LIBFT = libft/libft.a

BNAME = miniRT_bonus

BSRCS =	parse_bonus/tools.c 				\
		parse_bonus/tools2.c 				\
		parse_bonus/tools3.c 				\
		parse_bonus/parse.c 				\
		parse_bonus/whitesplit.c 			\
		parse_bonus/camera.c 				\
		parse_bonus/light.c 				\
		parse_bonus/ambient_lightning.c 	\
		parse_bonus/get_type.c				\
		parse_bonus/cylender.c 				\
		parse_bonus/sphere.c				\
		parse_bonus/plane.c \
		parse_bonus/cone.c	\
		parse_bonus/bonus_tools.c \
		free_bonus.c


COMMON =	camera.c \
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
			Objects/Sphere.c \
			Objects/Plane.c \
			Objects/Cylinder.c \
			Objects/Cylinder_utils.c \
			Materials/Diffuse.c \
			random.c \
			main.c

BSRCS +=	Materials/Simple_material.c \
			Materials/Specular.c \
			Materials/Reflection.c \
			textures/bump_map.c \
			textures/checker.c \
			Objects/Cone.c \
			Objects/Cone_utils.c \
			raytrace_bonus.c \
			init_objects_bonus.c 

SRCS = parse_mand/ambient_lightning.c \
	   parse_mand/camera.c \
	   parse_mand/cylender.c \
	   parse_mand/get_type.c \
	   parse_mand/light.c \
	   parse_mand/parse.c \
	   parse_mand/plane.c \
	   parse_mand/sphere.c \
	   parse_mand/tools.c \
	   parse_mand/tools2.c \
	   parse_mand/tools3.c \
	   parse_mand/whitesplit.c \
	   raytrace.c\
	   free_utils.c\
	   init_objects.c 

OBJS = $(COMMON:.c=.o)
OBJS += $(SRCS:.c=.o)

BOBJS = $(COMMON:.c=.o)
BOBJS += $(BSRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) ${LIBFT}
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

${LIBFT}:
	@make -C libft >/dev/null

bonus : $(BNAME)

$(BNAME) : $(NAME) $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) $(LDFLAGS) -o $(BNAME)

clean :
	@rm -rf $(OBJS) $(BOBJS)
	@make clean -C libft >/dev/null

fclean : clean
	@rm -rf $(NAME) libft/libft.a

re : fclean all

.PHONY : clean fclean all re
