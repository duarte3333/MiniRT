NAME = miniRT

CC = cc

CFLAGS = -O3 -Wall -Wextra -fsanitize=address -g#-Werror -fsanitize=address -g

SRCS = main.c \
	   draw.c \
	   object.c \
	   plane.c \
	   sphere.c \
	   hook.c \
	   vector.c \
	   raytracer.c

OBJS	= ${SRCS:.c=.o}

LIB_MINILIBX = -Lminilibx -lmlx -lXext -lX11 -lm -lz 

MINILIBX = minilibx/

all: $(NAME) lib

$(NAME): $(OBJS) lib
	$(CC) $(CFLAGS) $(OBJS) $(LIB_MINILIBX) -o $(NAME)

lib:
	make -C $(MINILIBX)

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
	make clean -C ${MINILIBX}

re: fclean all