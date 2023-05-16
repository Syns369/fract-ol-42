NAME        =fractol

LIBFT_DIR    =libft_42/

LIBFT_FILE    =libft.a

LIBFT        =$(LIBFT_DIR)$(LIBFT_FILE)

MLX_DIR        =minilibx-linux/

MLX_FILE    =libmlx.a

MLX            =$(MLX_DIR)$(MLX_FILE)

MLX_FLAGS    =-lX11 -lXext

SRC_DIR        =srcs/

OBJ_DIR        =objs/

INC_DIR        =includes/

INCS         = $(LIBFT_DIR)includes/libft.h includes/ft_printf.h
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall
RM = rm -rf
AR = ar rc
RANLIB = ranlib

SRC_FILES = main\
			fractals\

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

lib_ft:
	make all -C $(LIBFT_DIR)

mlx:
	make all -C $(MLX_DIR)

$(NAME):    lib_ft mlx $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -lm -lpthread -g3 

$(OBJ_DIR)%.o:        $(SRC_DIR)%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re