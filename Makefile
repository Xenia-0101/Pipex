NAME = pipex
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf
CC = cc
AR = ar rc

SRCS = src/

# *** libft library *** #
LIBFT_DIR = libft
LIBFT_NAME = libft.a

# *** source code files *** #
SRC = \
		main.c \
		${SRCS}ft_init_map.c \
		${SRCS}ft_open_files.c \
		${SRCS}ft_utils.c \
		${SRCS}ft_exec_cmd.c \
		# ${SRCS}ft_parse.c \
		# ${SRCS}ft_cmd.c \

OBJ = $(SRC:.c=.o)
HEADER = -I ./include/

all: libft ${NAME}
	@echo "pipex executable is ready"

%.o: %.c
	@${CC} ${CFLAGS} -c $< $(HEADER) -o $@

${NAME}: ${OBJ}
	${CC} -o ${NAME} ${OBJ} libft.a

# *** compile libft *** #
libft:
	@make -C libft
	@mv libft/libft.a ./
	@echo "libft library is ready"

# *** general rules *** #
clean:
	${RM} ${OBJ}
	make clean -C ${LIBFT_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re libft

# ls *.c | sed 's/$/ \\/'
