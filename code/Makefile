NAME = miniRT

CC = cc

CFLAGS = -O1 -Wall -Wextra -pthread #-fsanitize=address -g#-Werror -fsanitize=address -g

SRCS = Aux/pixel_put.c \
	   Aux/vector.c \
	   Aux/vector2.c \
	   Aux/ft_calloc.c \
	   Aux/ft_strlen.c \
	   Aux/get_next_line.c \
	   Aux/ft_isdigit.c \
	   Aux/strcmp_rt.c \
	   Aux/ft_atof.c \
	   Aux/ft_isspace.c \
	   Aux/ft_lists.c \
	   Aux/color.c \
	   Aux/color2.c \
	   Aux/free.c \
	   objects/object.c \
	   objects/plane.c \
	   objects/light_obj.c \
	   objects/sphere.c \
	   objects/cylinder.c \
	   objects/camera.c \
	   objects/cone.c \
	   parse/parse.c \
	   parse/parse2.c \
	   parse/syntax.c \
	   parse/syntax2.c \
	   parse/syntax3.c \
	   engine/light.c \
	   engine/light2.c \
	   engine/menu.c \
	   engine/hook.c \
	   engine/aux_ray.c \
	   engine/raytracer.c \
	   engine/aux_hook.c \
	   engine/mouse_hook.c \
	   engine/threads.c \
	   engine/rotations.c \
	   engine/paint.c \
	   engine/checkerboard.c \
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