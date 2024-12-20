# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=thread


# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIBFT_DIR := $(LIB_DIR)/libft

# Source files
SRC_FILES := $(SRC_DIR)/main.c \
$(SRC_DIR)/philo.c \
$(SRC_DIR)/errors/param_error.c \
$(SRC_DIR)/parsing/parsing.c \
$(SRC_DIR)/parsing/init_mutexes.c \
$(SRC_DIR)/parsing/init_structs.c \
$(SRC_DIR)/utils/atol.c \
$(SRC_DIR)/utils/ft_atost.c \
$(SRC_DIR)/utils/ft_get_current_time.c \
$(SRC_DIR)/utils/ft_usleep.c \
$(SRC_DIR)/utils/check_health.c \
$(SRC_DIR)/utils/clean_up.c \
$(SRC_DIR)/utils/ft_get_current_time.c \
$(SRC_DIR)/utils/ft_usleep.c \
$(SRC_DIR)/utils/routine.c \
$(SRC_DIR)/utils/check_health.c \
$(SRC_DIR)/utils/fork_checker.c \
$(SRC_DIR)/utils/is_dead.c \
$(SRC_DIR)/utils/philos_assemble.c \

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Libraries
LIBS := -L$(LIBFT_DIR) -lft 

# Executable
TARGET := philosopher
NAME := $(TARGET)

# Conditional compilation based on target
ifeq ($(MAKECMDGOALS),debug)
 CFLAGS += -g
else ifeq ($(MAKECMDGOALS),optimize)
 CFLAGS += -O2
endif

all: libft $(TARGET)

# Libft targets
libft:
	$(MAKE) -C $(LIBFT_DIR)

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) clean

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

clean: libft_clean 
	rm -rf $(OBJ_DIR)

fclean: clean libft_fclean 
	rm -f $(TARGET)

re: fclean all

bonus:: CFLAGS += -D BONUS=1
bonus: re

rebonus: fclean bonus

# Build rule
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Object file rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean fclean re bonus rebonus

