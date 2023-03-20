NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./includes
MLX_INCLUDE =
MLX_DIR=./mlx_linux
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

#source
SRCS_DIR = srcs/
SRCS = check_map.c create_map.c hooks.c error_message.c main.c fdf_utils.c \
		color.c draw.c zoom.c \

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#objsm
OBJS = $(SRCS_PREFIXED:.c=.o)

all : $(NAME)

%.o: %.c ./includes/fdf.h
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@
$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lm $(MLX_FLAGS) -o $(NAME)
	@echo $(NAME) is built

clean :
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(OBJS)
	@echo cleaning

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@rm -rf libmlx.dylib
	@echo "full clean"

re : fclean all

.PHONY	: all clean fclean re help