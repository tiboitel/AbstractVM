NAME				= abstractvm
SRCS				= main.cpp \
					  lexer.cpp \
					  factory.cpp \
					  exception.cpp \
					  machine.cpp
SRCSPATH			= ./srcs/
INCLUDES			= ./includes
CC					= g++
CFLAGS				= -std=c++11 -Wall -Werror -Wextra -O3
INCLUDES_C			= $(LFLAGS)
INCLUDES_O			= -I $(INCLUDES) -I ./libft/includes
SRC					= $(addprefix $(SRCSPATH), $(SRCS))
OBJS				= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES_O) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
