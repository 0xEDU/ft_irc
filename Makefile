SERVER_PORT = 6667
SERVER_PASSWORD = 123

NAME = ircserv
BONUS_NAME = ircbot

INCLUDES = -I ./includes/
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3

PATH_SRCS = ./srcs/
PATH_COMMANDS = ./srcs/commands/
PATH_CLASSES = ./srcs/classes/
PATH_BONUS = ./bonus/
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
				MODE.cpp \
				TOPIC.cpp \
				WHO.cpp \
				INVITE.cpp

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

BONUS_SRCS =	bot_bonus.cpp

BONUS_OBJS = ${BONUS_SRCS:%.cpp=$(PATH_OBJS)%.o}

all: $(NAME)
	@echo "\033[1;33m[INFO] Nothing to be done for '$@'.\033[0m"
	@echo "\033[1;33m[INFO] Use \`make run\` to start the server.\033[0m"

bonus: $(BONUS_NAME)
	
run: all
	./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)
	
v: all
	@valgrind --track-fds=yes --quiet ./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)

$(NAME): $(OBJS) $(CLASSES_OBJS) $(COMMANDS_OBJS) 
	@clang++ $(FLAGS) $(OBJS) $(CLASSES_OBJS) $(COMMANDS_OBJS) -o $(NAME)

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

$(BONUS_NAME): $(BONUS_OBJS)
	@clang++ $(FLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	
$(PATH_OBJS)%.o: $(PATH_BONUS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object" $@ "created!\033[0m"

clean:
	@rm -rf $(PATH_OBJS)
	@echo "\033[1;92m[SUCCESS] Object files removed!\033[0m"

fclean: clean
	@rm -rf $(NAME) $(TEST_NAME) $(BONUS_NAME)
	@echo "\033[1;92m[SUCCESS] Full clean done!\033[0m"

re: fclean all

rerun: re run

.PHONY: all run v tests client-tests clean fclean re rerun
