#include "../Server.hpp"

void	Server::printChannelInfo(int fd) {
	size_t	i = 0;
	writeln(fd, "  CHANNEL INFO ");
	for (; i < channels.size(); i++)
		channels[i].info(fd);
}
