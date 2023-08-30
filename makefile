
GREEN = \033[1;32m
RED = \033[1;31m
NO_COLOR = \033[0m

NAME = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC_DIR = src/
#OBJ_DIR = obj/
LIB_DIR = libft/

LIB = $(LIB_DIR)libft.a

RM = rm -rf

SRC_FILES = 	main.c\
				init.c

DEP = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.d))

TMP_SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC_FILES:.c=.o)

TMP_OBJ = $(addprefix $(OBJ_DIR), $(OBJ))

INCLUDE = -I ./include/ -I ./libft/

all : makelib $(OBJ_DIR) $(NAME)

makelib:
		make -C $(LIB_DIR)

#$(OBJ_DIR):
#		mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o  : $(SRC_DIR)%.c Makefile
	 			gcc $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@
				@echo "$(GREEN)file compiled$(NO_COLOR)"



$(NAME) : $(LIB)
		gcc $(CFLAGS) $(TMP_SRC) -L $(LIB_DIR) -lft -o $(NAME)
		@echo "$(GREEN)librairy compiled and executable generated$(NO_COLOR)" 



fclean : clean
		$(RM) $(NAME)
		$(RM) $(LIB)
		@echo "$(RED)full clean$(NO_COLOR)"

clean :
	$(RM) $(OBJ_DIR)
		$(MAKE) clean -C $(LIB_DIR)
		@echo "$(RED)objects directory removed$(NO_COLOR)"

re : fclean all

-include $(DEP)
.PHONY: all clean fclean re
