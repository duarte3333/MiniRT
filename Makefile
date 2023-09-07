NAME = miniRT

CC = cc

CFLAGS = -O1 -Wall -Wextra -fsanitize=address -g#-Werror -fsanitize=address -g

SRCS = Aux/pixel_put.c \
	   Aux/vector.c \
	   Aux/ft_calloc.c \
	   Aux/ft_strlen.c \
	   Aux/ft_strcmp.c \
	   Aux/ft_substr.c \
	   Aux/get_next_line.c \
	   Aux/ft_isdigit.c \
	   Aux/ft_strchr.c \
	   Aux/strcmp_rt.c \
	   Aux/ft_atof.c \
	   Aux/ft_isspace.c \
	   Aux/ft_lists.c \
	   main.c \
	   objects/object.c \
	   objects/plane.c \
	   objects/sphere.c \
	   objects/cylinder.c \
	   objects/light.c \
	   objects/camera.c \
	   hook.c \
	   raytracer.c \
	   parse.c \
	   color.c \
	   threads.c 

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