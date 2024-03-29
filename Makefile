# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 18:08:37 by ageiser           #+#    #+#              #
#    Updated: 2023/12/06 18:08:38 by ageiser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN = \033[1;32m
RED = \033[1;31m
NO_COLOR = \033[0m

NAME = philo

INCLUDE = philo.h

CFLAGS =  -Wall -Wextra -Werror #-fsanitize=thread

RM = rm -rf

SRC_FILES = 	main.c\
				init_and_run.c \
				philo.c \
				utils.c \
				libphil.c

OBJS	=	$(SRC_FILES:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
		gcc $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN)librairy compiled and executable generated$(NO_COLOR)" 

%.o: %.c $(INCLUDE)
		gcc $(CFLAGS) -c $< -o $@
		@echo "$(GREEN)Compiling$(NO_COLOR) $<"

fclean : clean
		$(RM) $(NAME)
		@echo "$(RED)full clean$(NO_COLOR)"

clean : 
		$(RM) $(OBJS)
		@echo "$(RED)clean$(NO_COLOR)"

re : fclean all

.PHONY: all clean fclean re