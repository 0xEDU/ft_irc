NAME = ircserv
TEST_NAME = ircserv_test

INCLUDES = -I ./includes/
TESTS_INCLUDES = -I ./tests/
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3

PATH_SRCS = ./srcs/
PATH_COMMANDS = ./srcs/commands/
PATH_CLASSES = ./srcs/classes/
PATH_TESTS = ./tests/
PATH_OBJS = ./objs/

SRCS =	main.cpp

COMMANDS_SRCS =	CAP.cpp \
				PASS.cpp \
				USER.cpp \
				LISTC.cpp \
				NICK.cpp \
				JOIN.cpp \
				PRIVMSG.cpp \
				QUIT.cpp \
				KICK.cpp \
				PART.cpp \
				WHO.cpp \
				MODE.cpp

CLASSES_SRCS =	Channel.cpp \
				Commands.cpp \
				CommandArgs.cpp \
				Client.cpp \
				RawMessage.cpp \
				Utils.cpp \
				Server.cpp

OBJS = ${SRCS:%.cpp=$(PATH_OBJS)%.o}
COMMANDS_OBJS = ${COMMANDS_SRCS:%.cpp=$(PATH_OBJS)%.o}
CLASSES_OBJS = ${CLASSES_SRCS:%.cpp=$(PATH_OBJS)%.o}

TESTS =	main_tests.cpp \
		RawMessage.cpp \
		parseMsg.cpp \
		split.cpp \
		Commands.cpp \
		Client.cpp

CLIENT_TESTS =	client_tests.cpp \
				Server.cpp \
				Client.cpp \
				RawMessage.cpp \
				Commands.cpp \
				NICK.cpp \
				PASS.cpp \
				USER.cpp \
				CAP.cpp \
				QUIT.CPP

TESTS_OBJS = ${TESTS:%.cpp=$(PATH_OBJS)%.o}
CLIENT_TESTS_OBJS = ${CLIENT_TESTS:%.cpp=$(PATH_OBJS)%.o}

SERVER_PORT = 6667
SERVER_PASSWORD = 123

all: $(NAME)
	
run: all
	@./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)
	
v: all
	@valgrind --track-fds=yes ./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)

$(NAME): $(OBJS) $(COMMANDS_OBJS) $(CLASSES_OBJS)
	@clang++ $(FLAGS) $(OBJS) $(COMMANDS_OBJS) $(CLASSES_OBJS) -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_COMMANDS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object" $@ "created!\033[0m"

$(PATH_OBJS)%.o: $(PATH_CLASSES)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object" $@ "created!\033[0m"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object" $@ "created!\033[0m"
	
tests: $(TESTS_OBJS)
	@echo "\033[1;92mRunning tests\033[0m"
	@clang++ $(FLAGS) $(TESTS_OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)
	
client-tests: $(CLIENT_TESTS_OBJS)
	@echo "\033[1;92mRunning client tests\033[0m"
	@clang++ $(FLAGS) $(CLIENT_TESTS_OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)

$(PATH_OBJS)%.o: $(PATH_TESTS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) $(TESTS_INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Test object" $@ "created!\033[0m"

clean:
	@rm -rf $(PATH_OBJS)
	@echo "\033[1;92m[SUCCESS] Object files removed!\033[0m"

fclean: clean
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "\033[1;92m[SUCCESS] Full clean done!\033[0m"

re: fclean all

.PHONY: all clean fclean re
