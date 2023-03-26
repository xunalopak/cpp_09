NAME = btc

SRC = $(shell find . -type f -name "*.cpp" | cut -c 3-)

CC = c++

FLAG = -Werror -Wall -Wextra -O2 -std=c++98

INCLUDES = $(shell find . -type f -name "*.hpp" | cut -c 3-)

OBJS	= $(SRC:.cpp=.o)

all:		$(NAME)

$(NAME): $(OBJS) $(INCLUDES)
			@$(CC) $(FLAG) -o $(NAME) $(OBJS)
%.o: %.cpp $(INCLUDES)
	@$(CC) $(FLAG) -c $< -o $@
	@printf "\033[32m[ ✔ ]\033[0m %s\n" "$<"

clean:
			@rm -f $(OBJS)

fclean: clean
			@rm -f $(NAME)

re:	fclean all