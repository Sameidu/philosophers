NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread
RM		=	rm -f
OBJ		=	$(SRC:.c=.o)
SRC		=	./philosophers/main.c \
			./philosophers/utils.c \
			./philosophers/list.c \
			./philosophers/init.c \
			./philosophers/routine.c \

CR	=	\033[0;31m
CG	=	\033[0;32m
CY	=	\033[0;33m
CB	=	\033[0;34m
CM	=	\033[0;35m
CCY	=	\033[0;36m
RC	=	\033[0m

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(CG)$(NAME) has been created.$(RC)"

all: $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo "$(CY)Object files have been removed. $(RC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CR)$(NAME) has been removed.$(RC)"

re: fclean all

.PHONY: all clean fclean re