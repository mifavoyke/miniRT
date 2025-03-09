NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -fPIE
RM := rm -rf

LIB_SRC :=	ft_atoi.c \
			ft_isascii.c \
			ft_memcmp.c \
			ft_putendl_fd.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strtrim.c \
			ft_bzero.c \
			ft_isdigit.c \
			ft_memcpy.c \
			ft_putnbr_fd.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_substr.c \
			ft_calloc.c \
			ft_isprint.c \
			ft_memmove.c \
			ft_putstr_fd.c \
			ft_strjoin.c \
			ft_strncmp.c \
			ft_tolower.c \
			ft_isalnum.c \
			ft_itoa.c \
			ft_memset.c \
			ft_split.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_toupper.c \
			ft_isalpha.c \
			ft_memchr.c \
			ft_putchar_fd.c \
			ft_strchr.c \
			ft_strlcpy.c \
			ft_strrchr.c \
			ft_get_next_line.c \
			ft_conversions.c \
			ft_printf_formats_cs%.c \
			ft_printf_formats_xX.c \
			ft_printf.c \
			ft_printf_formats_diu.c \
			ft_printf_formats_pointer.c \
			ft_lstadd_back.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstsize.c \
			ft_lstadd_front.c \
			ft_lstdelone.c \
			ft_lstlast.c \
			ft_lstnew.c

LIB_OBJS = $(LIB_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB_OBJS)
	@ar rc $(NAME) $(LIB_OBJS)

clean:
	@$(RM) $(LIB_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(LIB_OBJS)