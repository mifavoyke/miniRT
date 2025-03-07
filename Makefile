NAME := miniRT
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
CC := cc
RM := rm -rf
HEADERS = -I ./includes -I ./lib/MLX42/include/MLX42 -I ./lib/libft

SRC_DIR := ./src
LIBFT_DIR := ./lib/libft
MLX42_DIR = ./lib/MLX42
MLX42_BUILD = ./lib/MLX42/build
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

ifeq ($(shell uname), Darwin)
LIBS := $(MLX42_BUILD)/libmlx42.a -L/opt/homebrew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
LIBS := $(MLX42_BUILD)/libmlx42.a -ldl -lglfw -pthread -lm
endif

SRCS := $(SRC_DIR)/minirt.c \
		$(SRC_DIR)/minirt_utils.c \
		$(SRC_DIR)/hooks.c \
		$(SRC_DIR)/parse_scene.c \
		$(SRC_DIR)/parse_utils.c \
		$(SRC_DIR)/get_next_line/get_next_line.c \
		$(SRC_DIR)/get_next_line/get_next_line_utils.c \
		$(SRC_DIR)/ft_split.c

OBJS := ${SRCS:.c=.o}

all: libmlx libft $(NAME)

check_mlx:
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "MLX42 not found, cloning from GitHub..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	elif [ -z "$(shell ls $(MLX42_DIR))" ]; then \
		echo "MLX42 directory is empty, cloning from GitHub..."; \
		rm -rf $(MLX42_DIR); \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 exists, pulling latest updates..."; \
		cd $(MLX42_DIR) && git pull; \
	fi

libmlx: check_mlx
	@cmake -DDEBUG=1 $(MLX42_DIR) -B $(MLX42_BUILD) && make -C $(MLX42_BUILD) -j4

libft:
	@echo "\033[0;35mCompiling...\033[0m"
	@make all -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(MLX42_BUILD)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r ./lib/MLX42
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libmlx

.SILENT: $(OBJS)
