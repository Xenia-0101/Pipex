NAME = pipex
# CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf
CC = cc
AR = ar rc

HEADER = -I ./include/

# *** libft library *** #
LIBFT_DIR = libft
LIBFT_NAME = libft.a

# *** source code files *** #
SRC_PATH = src/
SRC = \
		main.c \
		ft_init_map.c \
		ft_open_files.c \
		ft_utils.c \
		ft_exec_cmd.c \
		ft_get_paths.c \
		ft_free.c \
		ft_get_full_path.c
SRCS := $(addprefix $(SRC_PATH), $(SRC))

# *** object files *** #
OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: libft ${NAME}
	@echo "pipex executable is ready"

${OBJ_PATH}%.o: ${SRC_PATH}%.c
	@${CC} ${CFLAGS} -c $< $(HEADER) -o $@

${OBJS}: ${OBJ_PATH}

${OBJ_PATH}:
	@mkdir ${OBJ_PATH}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} libft.a

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
