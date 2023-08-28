NAME = ircserv
TEST_NAME = ircserv_test

PATH_SRCS = ./srcs/
PATH_TESTS = ./tests/
PATH_OBJS = ./objs/

SRCS =	main.cpp \
		getPort.cpp \
		setupTCP.cpp \
		mainLoop.cpp \
		treatClientMessage.cpp \
		receiveMessage.cpp \
		Channel.cpp \
		Client.cpp \
		registerClient.cpp \
		validateClient.cpp \
		Message.cpp \
		parseMsg.cpp

OBJS = ${SRCS:%.cpp=$(PATH_OBJS)%.o}
	
TESTS =	main_tests.cpp \
		Message.cpp \
		parseMsg.cpp

CLIENT_TESTS =	client_tests.cpp \
				getPort.cpp \
				setupTCP.cpp \
				Client.cpp \
				Message.cpp \

TESTS_OBJS = ${TESTS:%.cpp=$(PATH_OBJS)%.o}
CLIENT_TESTS_OBJS = ${CLIENT_TESTS:%.cpp=$(PATH_OBJS)%.o}

INCLUDES = -I ./includes/
TESTS_INCLUDES = -I ./tests/
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
	
tests: $(TESTS_OBJS)
	@echo "\033[1;92mRunning tests\033[0m"
	@c++ $(FLAGS) $(TESTS_OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)
	
client-tests: $(CLIENT_TESTS_OBJS)
	@echo "\033[1;92mRunning client tests\033[0m"
	@c++ $(FLAGS) $(CLIENT_TESTS_OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)

$(PATH_OBJS)%.o: $(PATH_TESTS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@c++ $(FLAGS) $(INCLUDES) $(TESTS_INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Test object creation done!\033[0m"

clean:
	@rm -rf $(PATH_OBJS)
	@echo "\033[1;92m[SUCCESS] Object removed!\033[0m"

fclean: clean
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "\033[1;92m[SUCCESS] Full clean done!\033[0m"

re: fclean all

.PHONY: all clean fclean re
