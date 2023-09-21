NAME = miniRT

CC = cc

CFLAGS = -O1 -Wall -Wextra -pthread#-fsanitize=address -g#-Werror -fsanitize=address -g

SRCS = Aux/pixel_put.c \
	   Aux/vector.c \
	   Aux/ft_calloc.c \
	   Aux/ft_strlen.c \
	   Aux/get_next_line.c \
	   Aux/ft_isdigit.c \
	   Aux/strcmp_rt.c \
	   Aux/ft_atof.c \
	   Aux/ft_isspace.c \
	   Aux/ft_lists.c \
	   Aux/color.c \
	   objects/object.c \
	   objects/plane.c \
	   objects/sphere.c \
	   objects/cylinder.c \
	   objects/light.c \
	   objects/camera.c \
	   objects/cone.c \
	   parse/parse.c \
	   parse/syntax.c \
	   engine/hook.c \
	   engine/aux_ray.c \
	   engine/raytracer.c \
	   engine/threads.c \
	   engine/paint.c \
	   main.c 

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