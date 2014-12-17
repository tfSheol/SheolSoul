CC 		= g++

RM 		= rm -rf

PATH_SOURCES	= ./sources

CPPFLAGS 	+= -Wextra -Wall -Werror -g
CPPFLAGS 	+= -ansi -pedantic
CPPFLAGS 	+= -I./includes/

LDFLAGS 	+= $(CPPFLAGS) -lws2_32

NAME 		= SheolSoul

SRCS		= $(PATH_SOURCES)/main.cpp	    \
		  $(PATH_SOURCES)/MySoul.cpp	    \
		  $(PATH_SOURCES)/MySocket.cpp	    \
		  $(PATH_SOURCES)/md5.cpp

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
