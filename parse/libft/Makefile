
NAME	=	libft.a

SRCS	=		ft_isalpha.c	\
				ft_isprint.c	\
				ft_isdigit.c	\
				ft_isalnum.c	\
				ft_isascii.c	\
				ft_toupper.c	\
				ft_tolower.c	\
				ft_strlen.c		\
				ft_strchr.c		\
				ft_strrchr.c	\
				ft_memset.c		\
				ft_strncmp.c	\
				ft_atoi.c		\
				ft_strlcat.c	\
				ft_strlcpy.c	\
				ft_bzero.c		\
				ft_strnstr.c	\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_memcmp.c		\
				ft_memchr.c		\
				ft_strdup.c 	\
				ft_calloc.c 	\
				ft_putchar_fd.c \
				ft_substr.c		\
				ft_strtrim.c	\
				ft_putstr_fd.c	\
				ft_putnbr_fd.c	\
				ft_putendl_fd.c	\
				ft_strjoin.c	\
				ft_strmapi.c	\
				ft_split.c		\
				ft_itoa.c		\
				ft_striteri.c	\

SRCSBONUS =		ft_lstnew_bonus.c			\
				ft_lstadd_front_bonus.c		\
				ft_lstsize_bonus.c			\
				ft_lstlast_bonus.c			\
				ft_lstadd_back_bonus.c		\
				ft_lstdelone_bonus.c		\
				ft_lstclear_bonus.c			\
				ft_lstiter_bonus.c			\
				ft_lstmap_bonus.c

OBJBONUS = 	${SRCSBONUS:.c=.o}


OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

CC = cc

CFLAGS	=	-Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	@ar -rc ${NAME} ${OBJS}

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:		${OBJS} ${OBJBONUS}
	@ar -rc ${NAME} ${OBJS} ${OBJBONUS}

clean:
	@${RM} ${OBJS} ${OBJBONUS}

fclean: clean
	@${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean all re