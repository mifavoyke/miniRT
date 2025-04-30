NAME := miniRT
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -O3 -ffast-math -g
CC := cc
RM := rm -rf
HEADERS = -I ./includes -I ./lib/MLX42/include/MLX42 -I ./lib/libft

SRC_DIR := ./src
OBJ_DIR = ./obj
LIBFT_DIR := ./lib/libft
MLX42_DIR = ./lib/MLX42
MLX42_BUILD = ./lib/MLX42/build
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

ifeq ($(shell uname), Darwin)
LIBS := $(MLX42_BUILD)/libmlx42.a -L/usr/local/opt -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
LIBS := $(MLX42_BUILD)/libmlx42.a -ldl -lglfw -pthread -lm
endif

SRCS := $(SRC_DIR)/minirt.c \
		$(SRC_DIR)/math/basic.c \
		$(SRC_DIR)/math/intersections.c \
		$(SRC_DIR)/math/light.c \
		$(SRC_DIR)/math/math.c \
		$(SRC_DIR)/math/shadow.c \
		$(SRC_DIR)/math/vector_i.c \
		$(SRC_DIR)/math/vector_ii.c \
		$(SRC_DIR)/math/vector_iii.c \
		$(SRC_DIR)/parsing/color_utils.c \
		$(SRC_DIR)/parsing/coord_utils.c \
		$(SRC_DIR)/parsing/file_data.c \
		$(SRC_DIR)/parsing/fill_objects_a.c \
		$(SRC_DIR)/parsing/fill_objects_b.c \
		$(SRC_DIR)/parsing/fill_scene.c \
		$(SRC_DIR)/parsing/parse_scene.c \
		$(SRC_DIR)/parsing/parse_utils.c \
		$(SRC_DIR)/utils/allocate.c \
		$(SRC_DIR)/utils/array_utils.c \
		$(SRC_DIR)/utils/free.c \
		$(SRC_DIR)/utils/ft_atof.c \
		$(SRC_DIR)/utils/hooks.c \
		$(SRC_DIR)/utils/hook_functions.c \
		$(SRC_DIR)/utils/init.c \
		$(SRC_DIR)/utils/list_utils.c \
		$(SRC_DIR)/utils/string_utils.c \
		$(SRC_DIR)/utils/test_utils.c \
		$(SRC_DIR)/utils/utils.c 

# OBJS :=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS = $(SRCS:.c=.o) # when we put object files into a directory it does not take the files from subdirectiories of src/

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@$(RM) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(MLX42_BUILD)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) ./lib/MLX42
	@make fclean -C $(LIBFT_DIR)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx.supp ./$(NAME) scenes/basic.rt

re: fclean all

.PHONY: all clean fclean re libmlx libft

.SILENT: $(OBJS)
