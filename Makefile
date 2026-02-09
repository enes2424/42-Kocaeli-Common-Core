CXX = c++
RM = rm -f
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98
NAME = ircserv

SRCS	=	main.cpp Server.cpp Utils.cpp\
			Client.cpp Channel.cpp \
			commands/NICK.cpp commands/INFO.cpp \
			commands/JOIN.cpp commands/PRIVMSG.cpp \
			commands/EXIT_AND_QUIT.cpp commands/CHANNELINFO.cpp \
			commands/PART.cpp commands/INVITE.cpp commands/WHO.cpp \
			commands/KICK.cpp commands/MODE.cpp commands/TOPIC.cpp \
			commands/CAP.cpp commands/PASS.cpp commands/USER.cpp

OSRCS	=	$(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OSRCS)
	$(CXX) $(CXXFLAGS) $(OSRCS) -o $(NAME)

c : clean
clean :
	$(RM) $(OSRCS)

f : fclean
fclean : clean
	$(RM) $(NAME)

r: re
re : fclean
	make

.PHONY : all clean fclean re