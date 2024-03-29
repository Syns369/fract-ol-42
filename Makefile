NAME = fractol

LIBFT_DIR = libft-42/

LIBFT_FILE = libft.a

LIBFT = $(LIBFT_DIR)$(LIBFT_FILE)

MLX_DIR = minilibx-linux/

MLX_FILE=  libmlx.a

MLX = $(MLX_DIR)$(MLX_FILE)

MLX_FLAGS = -lX11 -lXext

SRC_DIR = srcs/

OBJ_DIR = objs/

INC_DIR = includes/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf
AR = ar rc
RANLIB = ranlib

SRC_FILES = main\
			fractals\
			navigation\
			pixels_manipulation\
			animation\
			utility\
			parsing\
			colors\
			

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(MLX):
	@make all -C $(MLX_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(MLX)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -lm

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c fractol.h | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re