NAME = raycasting

MLX_DIR = ./MLX42/build
LIBMLX = -lmlx42 -ldl -lglfw -pthread -lm #acho que só lglfw é dependencia

SRC = main.c

all: 
	gcc -o $(NAME) $(SRC) -L$(MLX_DIR) $(LIBMLX)
