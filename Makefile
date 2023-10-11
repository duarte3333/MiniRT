NAME = miniRT

CC = cc

CFLAGS = -O1 -Wall -Wextra -pthread #-fsanitize=address -g#-Werror -fsanitize=address -g

SRCS = code/Aux/pixel_put.c \
	   code/Aux/vector.c \
	   code/Aux/vector2.c \
	   code/Aux/ft_calloc.c \
	   code/Aux/ft_strlen.c \
	   code/Aux/get_next_line.c \
	   code/Aux/ft_isdigit.c \
	   code/Aux/strcmp_rt.c \
	   code/Aux/ft_atof.c \
	   code/Aux/ft_isspace.c \
	   code/Aux/ft_lists.c \
	   code/Aux/color.c \
	   code/Aux/color2.c \
	   code/Aux/free.c \
	   code/objects/object.c \
	   code/objects/plane.c \
	   code/objects/light_obj.c \
	   code/objects/sphere.c \
	   code/objects/cylinder.c \
	   code/objects/camera.c \
	   code/objects/cone.c \
	   code/parse/parse.c \
	   code/parse/parse2.c \
	   code/parse/syntax.c \
	   code/parse/syntax2.c \
	   code/parse/syntax3.c \
	   code/engine/light.c \
	   code/engine/light2.c \
	   code/engine/menu.c \
	   code/engine/hook.c \
	   code/engine/aux_ray.c \
	   code/engine/raytracer.c \
	   code/engine/aux_hook.c \
	   code/engine/mouse_hook.c \
	   code/engine/threads.c \
	   code/engine/rotations.c \
	   code/engine/paint.c \
	   code/engine/checkerboard.c \
	   code/main.c 

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