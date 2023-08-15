NAME = ircserv

PATH_SRCS = ./srcs/
PATH_OBJS = ./objs/

SRCS = main.cpp getPort.cpp setupTCP.cpp mainLoop.cpp

OBJS = ${SRCS:%.cpp=$(PATH_OBJS)%.o}

INCLUDES = -I ./includes/
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3

all: $(NAME)
	
run: all
	@./$(NAME) 6667 123
	
v: all
	@valgrind --track-fds=yes ./$(NAME) 6667 123

$(NAME): $(OBJS)
	@c++ $(FLAGS) $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@c++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object creation done!\033[0m"

clean:
	@rm -rf $(PATH_OBJS)
	@echo "\033[1;92m[SUCCESS] Object removed!\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;92m[SUCCESS] Full clean done!\033[0m"

re: fclean all

.PHONY: all clean fclean re
