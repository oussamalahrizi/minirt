NAME 	= minirt

BONUS 	= minirt_bonus

SRCS =	mandatory/parse/tools.c 				\
		mandatory/parse/tools2.c 				\
		mandatory/parse/tools3.c 				\
		mandatory/parse/parse.c 				\
		mandatory/parse/whitesplit.c 			\
		mandatory/parse/camera.c 				\
		mandatory/parse/light.c 				\
		mandatory/parse/ambient_lightning.c 	\
		mandatory/parse/get_type.c			\
		mandatory/parse/cylender.c 			\
		mandatory/parse/sphere.c				\
		mandatory/parse/plane.c

SRCS +=	mandatory/camera.c \
		mandatory/vectors.c \
		mandatory/vectors2.c \
		mandatory/vectors3.c \
		mandatory/Matrix/init.c \
		mandatory/Matrix/inverse.c \
		mandatory/Matrix/matrix.c \
		mandatory/Matrix/Minor.c \
		mandatory/Matrix/Multiplication.c \
		mandatory/Transformation/Gtfm.c \
		mandatory/Transformation/setup.c \
		mandatory/image/image.c \
		mandatory/image/image_utils.c \
		mandatory/Normals.c \
		mandatory/raytrace.c \
		mandatory/Objects/Sphere.c \
		mandatory/Objects/Plane.c \
		mandatory/Objects/Cylinder.c \
		mandatory/Objects/Cylinder_utils.c \
		mandatory/Materials/Diffuse.c \
		mandatory/free_utils.c \
		mandatory/random.c \
		mandatory/init_objects.c \
		mandatory/main_mandatory.c

SRCBONUS =	bonus/parse/tools.c 				\
			bonus/parse/tools2.c 				\
			bonus/parse/tools3.c 				\
			bonus/parse/parse.c 				\
			bonus/parse/whitesplit.c 			\
			bonus/parse/camera.c 				\
			bonus/parse/light.c 				\
			bonus/parse/ambient_lightning.c 	\
			bonus/parse/get_type.c				\
			bonus/parse/cylender.c 				\
			bonus/parse/sphere.c				\
			bonus/parse/plane.c 				\
			bonus/parse/cone.c					\
			bonus/parse/bonus_tools.c 

SRCBONUS +=	bonus/camera.c \
			bonus/vectors.c \
			bonus/vectors2.c \
			bonus/vectors3.c \
			bonus/Matrix/init.c \
			bonus/Matrix/inverse.c \
			bonus/Matrix/matrix.c \
			bonus/Matrix/Minor.c \
			bonus/Matrix/Multiplication.c \
			bonus/Transformation/Gtfm.c \
			bonus/Transformation/setup.c \
			bonus/image/image.c \
			bonus/image/image_utils.c \
			bonus/Normals.c \
			bonus/raytrace.c \
			bonus/init_objects.c \
			bonus/Objects/Sphere.c \
			bonus/Objects/Plane.c \
			bonus/Objects/Cylinder.c \
			bonus/Objects/Cylinder_utils.c \
			bonus/Objects/Cone.c \
			bonus/Objects/Cone_utils.c \
			bonus/Materials/Diffuse.c \
			bonus/Materials/Specular.c \
			bonus/Materials/Simple_material.c \
			bonus/Materials/Reflection.c \
			bonus/textures/checker.c \
			bonus/textures/checker_setup.c \
			bonus/textures/bump_map.c \
			bonus/main_bonus.c \
			bonus/random.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCBONUS:.c=.o}

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

CC = cc

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -Llibft -lft -lmlx -lXext -lX11 -lm

RM = rm -rf

all : ${NAME}

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS} $(LIBFT)
	@${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

${LIBFT}:
	@make -C libft >/dev/null

clean:
	@${RM} ${OBJS} ${OBJSBONUS}
	@make clean -C libft >/dev/null

bonus : ${BONUS}

${BONUS}: ${OBJSBONUS} $(LIBFT)
	@${CC} ${CFLAGS} ${OBJSBONUS} ${LDFLAGS} -o ${BONUS}

fclean: clean
	@${RM} ${NAME} ${BONUS} libft/libft.a

re:	fclean all

.PHONY:	clean fclean all re


