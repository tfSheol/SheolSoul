CC 		= g++

RM 		= rm -rf

CPPFLAGS 	+= -Wextra -Wall -Werror -g
CPPFLAGS 	+= -ansi -pedantic
CPPFLAGS 	+= -I.

LDFLAGS 	+= $(CPPFLAGS) -lws2_32

NAME 		= SheolSoul

SRCS		= main.cpp 	\
		  MySoul.cpp	\
		  MySocket.cpp	\
		  md5.cpp

OBJS 		= $(SRCS:.cpp=.o)


$(NAME): 	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: 		$(NAME)

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME).exe

re:		fclean all

.PHONY: 	all clean fclean re
